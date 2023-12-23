#ifndef COLOUR_H
#define COLOUR_H

#include "interval.h"

#include <glm/vec3.hpp>
#include <iostream>

void write_pixel_colour(std::ostream& out, glm::vec3 pixel_colour, int spp);

#endif // !COLOUR_H
