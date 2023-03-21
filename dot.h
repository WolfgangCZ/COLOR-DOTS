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

        Color get_color_from_number()
        {
            //std::cout << "inside get color" << std::endl;
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

        Vector2 m_pos{static_cast<float>(GetRandomValue(0,screen_w)),static_cast<float>(GetRandomValue(0,screen_h))}; //initialized on random position on map
        Vector2 m_vel {0,0};
        float m_radius {2};

        int m_color {GetRandomValue(0,6)}; //colors by number
        Color m_color_true {get_color_from_number()};
};