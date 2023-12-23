#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "ray.h"
#include "utils.h"

#include <glm/vec3.hpp>

class Hit_Record;

class Material
{
public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray& ray, const Hit_Record& record,
        glm::vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
private:
    glm::vec3 albedo;

public:
    Lambertian(const glm::vec3& albedo)
    {
        this->albedo = albedo;
    }

    bool near_zero(const glm::vec3& vec) const
    {
        float tol = 1e-8f;
        return (std::fabs(vec.x) < tol) && std::fabs(vec.y) < tol &&
            std::fabs(vec.z) < tol;
    }

    bool scatter(const Ray& ray, const Hit_Record& record,
        glm::vec3& attenuation, Ray& scattered) const override
    {
        glm::vec3 scatter_direction = record.normal + gen_random_unit_vec();

        if (near_zero(scatter_direction))
        {
            scatter_direction = record.normal;
        }

        scattered = Ray(record.point, scatter_direction);
        attenuation = this->albedo;
        return 1;
    }
};

class Metal : public Material
{
private:
    glm::vec3 albedo;
    float fuzz;

public:
    Metal(const glm::vec3& albedo)
    {
        this->albedo = albedo;
        this->fuzz = 1.0f;
    }

    Metal(const glm::vec3& albedo, const float fuzz)
    {
        this->albedo = albedo;
        this->fuzz = std::min(fuzz, 1.0f);
    }

    glm::vec3 reflect(const glm::vec3& vec, const glm::vec3& normal) const
    {
        return vec - normal * glm::dot(vec, normal) * 2.0f;
    }

    bool scatter(const Ray& ray, const Hit_Record& record,
        glm::vec3& attenuation, Ray& scattered) const override
    {
        glm::vec3 reflected = reflect(glm::normalize(ray.get_direction()),
            record.normal);

        scattered = Ray(record.point, reflected + gen_random_unit_vec() * this->fuzz);
        attenuation = this->albedo;
        return glm::dot(scattered.get_direction(), record.normal) > 0;
    }
};

class Dielectric : public Material
{
private:
    float refraction_index;

public:
    Dielectric(const float ir)
    {
        this->refraction_index = ir;
    }

    glm::vec3 refract(const glm::vec3& uv, const glm::vec3& normal, const float etai_over_etat) const
    {
        float cos_theta = std::fmin(glm::dot(uv * -1.0f, normal), 1.0f);
        glm::vec3 out_perpendicular = (uv + (normal*cos_theta)) * etai_over_etat;
        glm::vec3 out_parallel = normal * -1.0f * (float)sqrt(
            std::fabs(1.0 - glm::length2(out_perpendicular)));
        return (out_perpendicular + out_parallel);
    }

    glm::vec3 reflect(const glm::vec3& vec, const glm::vec3& normal) const
    {
        return vec - normal * glm::dot(vec, normal) * 2.0f;
    }

    float reflectance(const float cosine, const float ref_idx) const
    {
        float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
        r0 *= r0;
        return r0 + (1.0f - r0) * pow((1 - cosine), 5);
    }

    bool scatter(const Ray& ray, const Hit_Record& record,
        glm::vec3& attenuation, Ray& scattered) const override
    {
        attenuation = glm::vec3(1.0, 1.0, 1.0);
        float refraction_ratio = record.front_face ? (1.0 / refraction_index) : refraction_index;
        glm::vec3 normalized = glm::normalize(ray.get_direction());
        
        float c_theta = std::fmin(glm::dot(normalized * -1.0f, record.normal), 1.0f);
        float s_theta = sqrt(1.0f - pow(c_theta, 2));

        bool cant_refract = refraction_ratio * s_theta > 1.0;
        glm::vec3 dir;

        if (cant_refract || reflectance(c_theta, refraction_ratio) > gen_random_float())
        {
            dir = reflect(normalized, record.normal);
        }
        else
        {
            dir = refract(normalized, record.normal, refraction_ratio);
        }

        scattered = Ray(record.point, dir);
        return true;
    }
};

#endif
