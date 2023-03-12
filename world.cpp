#include "world.h"


#include <vector>
#include <memory>



void WorldPopulation::add_dot()
{
    //std::vector<LifeForm> world_animals{};
    all_dots.push_back(std::make_shared<ColorDot>(ColorDot{}));
}

void WorldPopulation::remove_dot()
{
    if(all_dots.size() > 0)
    all_dots.erase(all_dots.end());
}

void WorldPopulation::draw_dots()
{
    std::shared_ptr<ColorDot> pointer = nullptr;
    for(size_t i {0}; i<all_dots.size(); i++)
    {
        pointer = all_dots[i];
        pointer->update_draw();
    }
}

void WorldPopulation::update_dots_movement()
{
    std::shared_ptr<ColorDot> pointer = nullptr;
    for(size_t i {0}; i<all_dots.size(); i++)
    {
        pointer = all_dots[i];
        pointer->update_position();
    }
}

void WorldPopulation::update_dots_velocity()
{

    for(size_t i {0}; i<all_dots.size(); i++)
    {
        for(size_t j {i}; j<all_dots.size()-i; j++)
        {
            all_dots[i]->calc_vel_x(all_dots[j]);
            all_dots[i]->calc_vel_y(all_dots[j]);
        }
    }
}


