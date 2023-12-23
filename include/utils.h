#ifndef UTILS_H
#define UTILS_H

#include<cmath>
#include <glm/vec3.hpp>
#include <glm/gtx/norm.hpp>
#include <random>

inline float gen_random_float()
{
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    std::mt19937 generator;
    return distribution(generator);
}

inline float gen_random_float(const float min, const float max)
{
    return min + (max - min) * gen_random_float();
}

inline glm::vec3 gen_random_vec()
{
    return glm::vec3(gen_random_float(), gen_random_float(), gen_random_float());
}

inline glm::vec3 gen_random_vec(const float min, const float max)
{
    return glm::vec3(gen_random_float(min, max), gen_random_float(min, max), gen_random_float(min, max));
}

inline glm::vec3 gen_random_vec_in_us(int depth)
{
    glm::vec3 forced_vec = glm::normalize(gen_random_vec());
    forced_vec.x = forced_vec.x - 0.05;
    forced_vec.y = forced_vec.y - 0.05;
    forced_vec.y = forced_vec.z - 0.05;
    glm::vec3 rand = gen_random_vec();
    while (glm::length2(rand) > 1 and depth > 0)
    {
        rand = gen_random_vec();
        depth -= 1;
    }
    return depth == 0 ? forced_vec : rand;
}

inline glm::vec3 gen_random_unit_vec()
{
    return glm::normalize(gen_random_vec_in_us(20));
}

inline glm::vec3 gen_random_on_hemisphere(const glm::vec3& normal)
{
    glm::vec3 rand_unit = gen_random_unit_vec();
    if (glm::dot(normal, rand_unit) > 0.0)
    {
        return rand_unit;
    }
    return rand_unit * -1.0f;
}

#endif // !UTILS_H
