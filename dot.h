#include "global_var.h"

struct Dot
{
    public:
        Dot() = default;
        Dot(float x, float y, float v_x, float v_y, Color color)
            : m_pos{x,y}, m_vel{0,0}, m_color_true(color)
        {}
        ~Dot()
        {}
        Dot *get_ptr()
        {
            return this;
        }
        void update_movement(const Dot &other_dot)
        {
            Vector2Add(m_pos, m_vel);
        }

        Vector2 m_pos{static_cast<float>(GetRandomValue(0,screen_w)),static_cast<float>(GetRandomValue(0,screen_h))}; //initialized on random position on map
        Vector2 m_vel {0,0};
        float m_radius {2};

        size_t m_color {GetRandomValue(0,6)}; //colors by number
        Color m_color_true {get_color_from_number(m_color)};
};