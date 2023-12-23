#include "interval.h"

Interval::Interval()
{
    this->min = -1 * std::numeric_limits<float>::infinity();
    this->max = std::numeric_limits<float>::infinity();
}

Interval::Interval(const float min, const float max)
{
    this->min = min;
    this->max = max;
}

bool Interval::contains(const float num) const
{
    return this->min <= num && num <= this->max;
}

bool Interval::surrounds(const float num) const
{
    return this->min < num && num < this->max;
}

float Interval::clamp(const float num) const
{
    if (num < this->min) return this->min;
    if (num > this->max) return this->max;
    return num;
}
