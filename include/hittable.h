#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "interval.h"

#include <glm/gtx/norm.hpp>
#include <memory>

class Material;

class Hit_Record
{
public:
    glm::vec3 point;
    glm::vec3 normal;
    float t;
    bool front_face;
    std::shared_ptr<Material> material;

    void set_normal(const Ray& ray, const glm::vec3& outward_normal)
    {
        this->front_face = glm::dot(ray.get_direction(), outward_normal) < 0;
        this->normal = front_face ? outward_normal : outward_normal * -1.0f;
    }
};

class Hittable
{
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, const Interval t_range, Hit_Record& record) const = 0;
};
#endif