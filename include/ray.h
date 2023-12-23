#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>

class Ray
{
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	Ray();
	Ray(const glm::vec3& origin, const glm::vec3& direction);

	glm::vec3 get_origin() const;
	glm::vec3 get_direction() const;

	glm::vec3 ray_function(const double t) const;
};
#endif
