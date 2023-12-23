#include "sphere.h"

Sphere::Sphere(const glm::vec3 origin, const float radius, std::shared_ptr<Material> mat)
{
	this->origin = origin;
	this->radius = radius;
	this->material = mat;
}

bool Sphere::hit(const Ray& ray, const Interval t_range, Hit_Record& record) const
{
	glm::vec3 vecCO = ray.get_origin() - this->origin;
	float a = glm::dot(ray.get_direction(), ray.get_direction());
	float half_b = glm::dot(vecCO, ray.get_direction());
	float c = glm::dot(vecCO, vecCO) - pow(radius, 2);
	float discriminant = pow(half_b, 2) - a * c;

	if (discriminant < 0)
	{
		return false;
	}

	float sqrtDiscriminant = sqrt(discriminant);
	float root = (-half_b - sqrtDiscriminant) / a;
	if (!t_range.surrounds(root))
	{
		root = (-half_b + sqrtDiscriminant) / a;
		if (!t_range.surrounds(root))
		{
			return false;
		}
	}

	record.t = root;
	record.point = ray.ray_function(root);
	glm::vec3 outward_normal = (record.point - this->origin) / this->radius;
	record.set_normal(ray, outward_normal);
	record.material = material;

	return true;	
}
