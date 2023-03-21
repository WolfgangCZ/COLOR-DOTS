#include <iostream>
#include <vector>
#include <memory>
//#include "dot.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
//#include "world.h"



extern const std::size_t screen_w{800};
extern const std::size_t screen_h{600};
extern const std::size_t starting_dots {0};
extern const float player_speed {0.1};
extern const float friction {0.9};
extern const float gravity_strenght {1};
extern const float repel_strenght {gravity_strenght*2};

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
                DrawCircle(all_dots[i]->m_pos.x, all_dots[i]->m_pos.y, all_dots[i]->m_radius, Color{WHITE});
                
            }
        }
    private:
        std::vector<std::shared_ptr<Dot>> all_dots {};
};

//fix it bitch
void get_gravity(Dot &this_dot, const Dot &other_dot)
{
    Vector2 distance = Vector2{Vector2Subtract(this_dot.m_pos,other_dot.m_pos)};     
    Vector2 gravity = {};
    if((distance.x < 1 && distance.x > -1))
    {
        if(distance.x != 0) distance.x /= abs(distance.x);
        
    }
    if((distance.y < 1 && distance.y > -1))
    {
        if(distance.y != 0) distance.y /= abs(distance.y);
    }

    gravity = Vector2{gravity_strenght/distance.x, gravity_strenght/distance.y};


    //use gravity
    if(distance.x != 0 && distance.y != 0)
    {
        this_dot.m_vel = Vector2Subtract(this_dot.m_vel, gravity);
    }    
    std::cout << "distance: " << Vector2Length(distance);
    std::cout << " gravity: " << Vector2Length(gravity) << std::endl;
}

void update_player_pos(Dot &player)
{
    player.m_pos = Vector2Add(player.m_pos, player.m_vel);
}

void draw_player(const Dot &player)
{
    DrawCircle(player.m_pos.x, player.m_pos.y, player.m_radius, Color{RED});
}

//--------------------------------------------------------------------------------------------
//MAIN FUNCTION
//--------------------------------------------------------------------------------------------

int main ()
{
    World world;
    Dot player {static_cast<float>(screen_w/2), static_cast<float>(screen_h/2),0,0};
    Dot other_dot {static_cast<float>(screen_w/3), static_cast<float>(screen_h/3),0,0};
    
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

        if(IsKeyDown(KEY_LEFT))
        {
        player.m_vel.x -= player_speed;
        }
        if(IsKeyDown(KEY_RIGHT))
        {
        player.m_vel.x += player_speed;
        }
        if(IsKeyDown(KEY_UP))
        {
        player.m_vel.y -= player_speed;
        }
        if(IsKeyDown(KEY_DOWN))
        {
        player.m_vel.y += player_speed;
        }



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
        
        draw_player(player);
        draw_player(other_dot);
        update_player_pos(player);
        update_player_pos(other_dot);
        get_gravity(player,other_dot);

        //friction
        player.m_vel.x *= friction;
        player.m_vel.y *= friction;

        /*
        world.update_dots_velocity();
        world.check_boundaries();
        world.update_dots_movement();
        */
        //world.draw_dots();
        
        EndMode2D();
        EndDrawing();
    }
    std::cout << "DONE! See ya ";
    return 0;
}