#include "world.h"
#include "utilities.h"

#include <vector>
#include <memory>

//TODO
//change to orto distance
//make gravity matrix as module somehow

void WorldPopulation::add_dot()
{
    //std::vector<LifeForm> world_animals{};
    all_dots.push_back(std::make_shared<ColorDot>(ColorDot{}));
}

void WorldPopulation::remove_dot()
{
    if(all_dots.size() > 0) all_dots.erase(all_dots.end());
}

void WorldPopulation::draw_dots()
{
    for(size_t i {0}; i<all_dots.size(); i++)
    {
        all_dots[i]->update_draw();
    }
}

void WorldPopulation::update_dots_movement()
{
    for(size_t i {0}; i<all_dots.size(); i++)
    {
        all_dots[i]->update_position();
    }
}



void WorldPopulation::update_dots_velocity()
{
    for(size_t i {0}; i<all_dots.size(); i++)
    {
        for(size_t j {0}; j<all_dots.size(); j++)
        {
            if(i==j) continue;
            //need to pas absolute values

            if(calculate_orto_lenght((all_dots[j]->m_x)-(all_dots[i]->m_x),(all_dots[j]->m_y)-(all_dots[i]->m_y)) < gravity_distance)
            {
                all_dots[i]->calc_vel_x(all_dots[j]);
                all_dots[i]->calc_vel_y(all_dots[j]);
            }
        }
    }
}

//check for boundaries
void WorldPopulation::check_boundaries()
{
        for(size_t i {0}; i<all_dots.size(); i++)
    {
        //left boundary
        if(all_dots[i]->m_x <= 0)
        {
            all_dots[i]->m_x = 0;
            all_dots[i]->m_vel_x *= -1*wall_bounciness;
        }
        //right boundary
        else if(all_dots[i]->m_x >= screen_width)
        {
            all_dots[i]->m_x = screen_width;
            all_dots[i]->m_vel_x *= -1*wall_bounciness;
        }
        //upper boundary
        else if(all_dots[i]->m_y <= 0)
        {
            all_dots[i]->m_y = 0;
            all_dots[i]->m_vel_y *= -1*wall_bounciness;
        }
        //lower boundary
        else if(all_dots[i]->m_y >= screen_height)
        {
            all_dots[i]->m_y = screen_height;
            all_dots[i]->m_vel_y *= -1*wall_bounciness;
        }
    }
}



