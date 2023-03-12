#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>
#include "color_dot.h"



/*
world population store all living life forms as dynamic array
functions in this class serve as updates for each frame (or some cycle based on performance in future? maybe)
also there is function for dynamicaly adding new creatures and plants or inherited creatures based on reproduction
*/

class WorldPopulation
{
    public:
    WorldPopulation()
    {}
    ~WorldPopulation()
    {}
    std::vector<std::shared_ptr<ColorDot>> all_dots{};
    //add all objects grid for calculating each distances x and y
    //sort this grid for first time and then for each recalculation check for chanigng order

    void add_dot();
    void remove_dot();
    void draw_dots();
    void update_dots_velocity();
    void update_dots_movement();

};


#endif //WORLD_H