#include <iostream>
#include <vector>
#include <memory>
//#include "dot.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
//#include "world.h"

#include "dot.h"
#include "global_var.h"





void get_gravity(std::shared_ptr<Dot> this_dot, const std::shared_ptr<Dot> other_dot)
{
    Vector2 distance = Vector2{Vector2Subtract(this_dot->m_pos,other_dot->m_pos)};     
    Vector2 gravity = Vector2Scale(Vector2Normalize(distance), gravity_strenght/Vector2Length(distance));
    Vector2 repel = Vector2Scale(Vector2Normalize(distance), repel_strenght/(Vector2LengthSqr(distance)));

    //use gravity
    if(distance.x != 0 && distance.y != 0)
    {
        this_dot->m_vel = Vector2Subtract(this_dot->m_vel, gravity);
        this_dot->m_vel = Vector2Add(this_dot->m_vel, repel);
    }    
    //std::cout << "distance: " << Vector2Length(distance);
    //std::cout << " gravity: " << Vector2Length(gravity) << std::endl;
}



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
            //check all dots with all dots and apply gravity
            for(std::size_t i {0}; i<all_dots.size(); i++)
            {
                for(std::size_t j {0}; j<all_dots.size(); ++j)
                {
                    if(i == j) continue;
                    get_gravity(all_dots[i], all_dots[j]);
                }
                //apply friction to speed
                all_dots[i]->m_vel = Vector2Scale(all_dots[i]->m_vel, friction);
                //update movement
                all_dots[i]->m_pos = Vector2Add(all_dots[i]->m_pos, all_dots[i]->m_vel);
                //draw dots
                DrawCircle(all_dots[i]->m_pos.x, all_dots[i]->m_pos.y, all_dots[i]->m_radius, Color{WHITE});
            }
        }
    private:
        std::vector<std::shared_ptr<Dot>> all_dots {};
};




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
        update_player_pos(player);
        world.draw_dots();



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