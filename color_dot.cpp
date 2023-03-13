#include <iostream>
#include <memory>

#include "color_dot.h"
#include "utilities.h"
#include "raylib.h"

ColorDot::ColorDot()
{
}

ColorDot::ColorDot(const ColorDot &tmp) : m_x(tmp.m_x), m_y(tmp.m_y), 
                                        m_vel_x(tmp.m_vel_x), m_vel_y(tmp.m_vel_y), 
                                        m_radius(tmp.m_radius), 
                                        m_color(tmp.m_color), m_color_true(tmp.m_color_true)
{
}


ColorDot::~ColorDot()
{
}




void ColorDot::update_draw()
{
    DrawCircle(m_x, m_y, m_radius, m_color_true);
}
void ColorDot::update_position()
{
    m_x += m_vel_x;
    m_y += m_vel_y;
    
}

//calculating velocity by calculating gravity for near objects
void ColorDot::calc_vel_x(const std::shared_ptr<ColorDot>& other_dot)
{
    m_vel_x += get_gravity(other_dot->m_x - m_x)
        *gravity_matrix[m_color][other_dot->m_color];
    if(m_vel_x > max_velocity || -m_vel_x>max_velocity) m_vel_x*= friction;
}

void ColorDot::calc_vel_y (const std::shared_ptr<ColorDot>& other_dot)
{
    m_vel_y += get_gravity(other_dot->m_y - m_y)
        *gravity_matrix[m_color][other_dot->m_color];
    if(m_vel_y > max_velocity || -m_vel_y>max_velocity) m_vel_y*= friction;
}

Color ColorDot::get_color()
{
    std::cout << "inside get color" << std::endl;
    switch (m_color)
    {
        case 0: 
            //std::cout << "getting gray" << std::endl;
            return Color{GRAY};
            break;
        case 1: 
            //std::cout << "getting red" << std::endl;
            return Color{RED};
            break;
        case 2: 
            //std::cout << "getting gold" << std::endl;
            return Color{GOLD};
            break;
        case 3: 
            //std::cout << "getting lime" << std::endl;
            return Color{LIME};
            break;
        case 4: 
            //std::cout << "getting blue" << std::endl;
            return Color{BLUE};
            break;
        case 5: 
            //std::cout << "getting violet" << std::endl;
            return Color{VIOLET};
            break;
        case 6: 
            //std::cout << "getting brown" << std::endl;
            return BROWN;
            break;       
        default:
            //std::cout << "WARINGNG default color of dot called!" << std::endl;
            return GRAY;
            break;
    }
    return GRAY;
}
