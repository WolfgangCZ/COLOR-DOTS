#ifndef COLOR_DOT_H
#define COLOR_DOT_H
#include "global_variables.h"
#include "raylib.h"

#include <memory>


struct ColorDot
{
    ColorDot();
    ColorDot(const ColorDot &tmp);
    ~ColorDot();

    void update_draw();
    void update_position();

    void calc_vel_x (const std::shared_ptr<ColorDot>& other_dot);
    void calc_vel_y (const std::shared_ptr<ColorDot>& other_dot);

    Color get_color();

    float m_x {static_cast<float>(GetRandomValue(200,600))};
    float m_y {static_cast<float>(GetRandomValue(200,600))};
    float m_vel_x {0};
    float m_vel_y {0};
    float m_radius {dot_radius};
    int m_color {GetRandomValue(0,6)}; //colors by number
    Color m_color_true {get_color()};
};

#endif //COLOR_DOT_H