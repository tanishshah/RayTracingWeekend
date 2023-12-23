#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

#include <glm/vec3.hpp>


class Sphere : public Hittable
{
private:
    glm::vec3 origin;
    float radius;
    std::shared_ptr<Material> material;

public:
    Sphere(const glm::vec3 origin, const float radius, std::shared_ptr<Material> mat);
    bool hit(const Ray& ray, const Interval t_range, Hit_Record& record) const override;
};

#endif