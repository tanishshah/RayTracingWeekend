#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

# include "hittable.h"

#include <vector>

class Hittable_List : public Hittable
{
public:
    std::vector<std::shared_ptr<Hittable>> hittables;
    Hittable_List() {}
    Hittable_List(std::shared_ptr<Hittable> hittable)
    {
        this->hittables.push_back(hittable);
    }

    bool hit(const Ray& ray, const Interval t_range, Hit_Record& record) const override
    {
        Hit_Record tmp;
        bool has_hit = false;
        float best = t_range.max;

        for (int i = 0; i < this->hittables.size(); i++)
        {
            if (hittables[i]->hit(ray, Interval(t_range.min, best), tmp))
            {
                has_hit = true;
                best = tmp.t;
                record = tmp;
            }
        }

        return has_hit;
    }
};

#endif
