#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits> 

class Interval
{
public:
    float min;
    float max;

    static const Interval empty;
    static const Interval universe;

    Interval();
    Interval(const float min, const float max);

    bool contains(const float num) const;
    bool surrounds(const float num) const;
    float clamp(const float num) const;
};

const static Interval empty(std::numeric_limits<float>::infinity(), -1 * std::numeric_limits<float>::infinity());
const static Interval universe(-1 * std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());

#endif