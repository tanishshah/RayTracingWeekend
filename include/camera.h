#ifndef CAMERA_H
#define CAMERA_H

#include "colour.h"
#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "utils.h"

#include <glm/vec3.hpp>
#include <iostream>
#include <random>

class Camera
{
private:
    const float ASPECT_RATIO = 16.0 / 9.0;
    const int WIDTH = 256;
    const int HEIGHT = std::max(1, static_cast<int>(WIDTH / ASPECT_RATIO));
    const int SAMPLES_PER_PIXEL = 10;
    const int MAX_DEPTH = 15;

    const float FOCAL_LENGTH = 1.0;
    const float VIEWPORT_HEIGHT = 2.0;
    const float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (static_cast<double>(WIDTH) / HEIGHT);
    const glm::vec3 CAMERA_ORIGIN = glm::vec3(0, 0, 0);

    const glm::vec3 VIEWPORT_U = glm::vec3(VIEWPORT_WIDTH, 0, 0);
    const glm::vec3 VIEWPORT_V = glm::vec3(0, -1 * VIEWPORT_HEIGHT, 0);

    const glm::vec3 PIXEL_DELTA_U = VIEWPORT_U / (float)WIDTH;
    const glm::vec3 PIXEL_DELTA_V = VIEWPORT_V / (float)HEIGHT;

    const glm::vec3 VIEWPORT_UPPER_LEFT = CAMERA_ORIGIN - glm::vec3(0, 0, FOCAL_LENGTH) -
        (VIEWPORT_U / (float)2) - (VIEWPORT_V / (float)2);
    const glm::vec3 PIXEL00_LOC = VIEWPORT_UPPER_LEFT + (PIXEL_DELTA_U + PIXEL_DELTA_V) *
        (float)0.5;

public:
    glm::vec3 pixel_sample_square() const;
    glm::vec3 ray_2_colour_vec(const Ray& ray, const Hittable& world, const int depth);

    void render(const Hittable& world);
    Ray generate_ray(const int i, const int j) const;

};
#endif // ! CAMERA_H
