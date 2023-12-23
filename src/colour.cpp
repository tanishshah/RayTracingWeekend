#include "colour.h"

void write_pixel_colour(std::ostream& out, glm::vec3 pixel_colour, int spp)
{
    pixel_colour = pixel_colour * (1.0f / spp);

    Interval intensity(0.000f, 0.999f);
    // sqrt for linear -> gamma
    out << static_cast<int>(256 * intensity.clamp(sqrt(pixel_colour.x))) << ' '
        << static_cast<int>(256 * intensity.clamp(sqrt(pixel_colour.y))) << ' '
        << static_cast<int>(256 * intensity.clamp(sqrt(pixel_colour.z))) << '\n';
}