#include "ray.h"

Ray::Ray() {}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
{
	this->origin = origin;
	this->direction = direction;
}

glm::vec3 Ray::ray_function(const double t) const
{
	return this->origin + direction * float(t);
}

glm::vec3 Ray::get_direction() const
{
	return this->direction;
}

glm::vec3 Ray::get_origin() const
{
	return this->origin;
}