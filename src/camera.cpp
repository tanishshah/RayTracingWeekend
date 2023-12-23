#include "camera.h"

glm::vec3  Camera::ray_2_colour_vec(const Ray& ray, const Hittable& world, const int depth)
{
    Hit_Record record;

    if (depth <= 0)
    {
        return glm::vec3(0.0, 0.0, 0.0);
    }

    if (world.hit(ray, Interval(0.001f, INFINITY), record))
    {
        Ray scattered;
        glm::vec3 attenuation(0.0);
        if (record.material->scatter(ray, record, attenuation, scattered))
        {
            return attenuation * ray_2_colour_vec(scattered, world, depth - 1);
        }
        return glm::vec3(0.0, 0.0, 0.0);
    }

    glm::vec3 unit_direction = glm::normalize(ray.get_direction());
    float a = 0.5 * (unit_direction.y + 1.0);
    return glm::vec3(1.0, 1.0, 1.0) * ((float)(1.0 - a)) + glm::vec3(0.5, 0.7, 1.0) * a;
}

glm::vec3 Camera::pixel_sample_square() const
{
    float px = -0.5 * gen_random_float();
    float py = -0.5 * gen_random_float();
    return (this->PIXEL_DELTA_U * px) + (this->PIXEL_DELTA_V * py);
}

Ray Camera::generate_ray(const int i, const int j) const
{
    glm::vec3 pixel_center = this->PIXEL00_LOC + (this->PIXEL_DELTA_U *
        (float)i) + (this->PIXEL_DELTA_V * (float)j);
    glm::vec3 pixel_sample = pixel_center + pixel_sample_square();
    glm::vec3 ray_direction = pixel_center - this->CAMERA_ORIGIN;
    return Ray(this->CAMERA_ORIGIN, ray_direction);
}

void Camera::render(const Hittable& world)
{
    std::cout << "P3\n" << this->WIDTH << ' ' << this->HEIGHT << "\n255\n";
    for (int j = 0; j < this->HEIGHT; ++j)
    {
        std::clog << "\rScanlines remaining: " << (this->HEIGHT - j) << ' ' << std::flush;
        for (int i = 0; i < this->WIDTH; ++i)
        {
            glm::vec3 pixel_colour = glm::vec3(0.0, 0.0, 0.0);
            for (int sample = 0; sample < this->SAMPLES_PER_PIXEL; sample++)
            {
                Ray ray = generate_ray(i, j);
                pixel_colour += ray_2_colour_vec(ray, world, this->MAX_DEPTH);
            }
            write_pixel_colour(std::cout, pixel_colour, this->SAMPLES_PER_PIXEL);
        }
    }
}