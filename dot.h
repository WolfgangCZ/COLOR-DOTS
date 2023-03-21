#include "global_var.h"

struct Dot
{
    public:
        Dot() = default;
        Dot(float x, float y, float v_x, float v_y)
            : m_pos{x,y}, m_vel{0,0}
        {}
        ~Dot()
        {}
        void update_movement(const Dot &other_dot)
        {
            Vector2Add(m_pos, m_vel);
        }

        Vector2 m_pos{static_cast<float>(GetRandomValue(0,screen_h)),static_cast<float>(GetRandomValue(0,screen_w))}; //initialized on random position on map
        Vector2 m_vel {0,0};
        float m_radius {2};
};