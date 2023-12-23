// Main for Raytracer based on Ray Tracing in One Weekend

#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main()
{
	Camera camera;
	Hittable_List world;
    auto material_ground = std::make_shared<Lambertian>(glm::vec3(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Dielectric>(1.5);
	world.hittables.push_back(std::make_shared<Sphere>(glm::vec3(0.0, 0.0, -1.0), 0.5, material_center));
    world.hittables.push_back(std::make_shared<Sphere>(glm::vec3(0.0, -100.5, -1.0), 100.0, material_ground));


	camera.render(world);
}