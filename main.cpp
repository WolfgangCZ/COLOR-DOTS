#include <iostream>
#include <vector>
#include <memory>
//#include "dot.h"
#include "raylib.h"
//#include "world.h"



extern const std::size_t screen_w{800};
extern const std::size_t screen_h{600};
extern const std::size_t starting_dots {400};

struct Dot
{
    public:
        Dot() = default;
        Dot(float x, float y, float v_x, float v_y)
            : m_x(x), m_y(y), m_vel_x(v_x), m_vel_y(v_y)
        {}
        ~Dot()
        {}

        float m_x {static_cast<float>(GetRandomValue(0,screen_w))};
        float m_y {static_cast<float>(GetRandomValue(0,screen_h))};
        float m_vel_x {0};
        float m_vel_y {0};
        float m_radius {2};
};

class World
{
    public:
        void add_dot_on_click()
        {
            all_dots.push_back(std::make_shared<Dot> (Dot{GetMousePosition().x, GetMousePosition().y,0.0f,0.0f}));
        }
        void add_rand_dot()
        {
            all_dots.push_back(std::make_shared<Dot> (Dot{}));
        }
        void remove_dot()
        {
            all_dots.pop_back();
        }
        void draw_dots()
        {
            for(std::size_t i {0}; i<all_dots.size(); i++)
            {
                DrawCircle(all_dots[i]->m_x, all_dots[i]->m_y, all_dots[i]->m_radius, Color{WHITE});
            }
        }
    private:
        std::vector<std::shared_ptr<Dot>> all_dots {};
};

int main ()
{
    World world;
    
    for(size_t i {0}; i<starting_dots; i++)
    {
        world.add_rand_dot();
    }
    InitWindow(screen_w, screen_h, "New window");

//setting up camera
    Vector2 camera_position {screen_w/2,screen_h/2};

    Camera2D camera {0};
    camera.target = camera_position;
    camera.offset = (Vector2){screen_w/2,screen_h/2};
    camera.rotation = 0;
    camera.zoom = 1;


    SetTargetFPS(60);
    while(WindowShouldClose()==false)
    {
        //-------------------------------------------------------------------------------
        //GAME LOGIC
        //-------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);

        if(IsKeyPressed(KEY_I))
        {
            std::cout << "key I pressed" << std::endl;
            world.add_rand_dot();
        }
        if(IsKeyPressed(KEY_O))
        {
            std::cout << "key O pressed" << std::endl;
            world.remove_dot();
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {  
            std::cout << "mouse left button pressed" << std::endl;
            world.add_dot_on_click();
        }
        
        /*
        world.update_dots_velocity();
        world.check_boundaries();
        world.update_dots_movement();
        */
        world.draw_dots();
        
        EndMode2D();
        EndDrawing();
    }
    std::cout << "DONE! See ya ";
    return 0;
}