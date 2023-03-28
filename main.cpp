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




//limit applied force
void get_gravity_v1(std::shared_ptr<Dot> this_dot, const std::shared_ptr<Dot> other_dot)
{
    Vector2 distance = Vector2{Vector2Subtract(this_dot->m_pos,other_dot->m_pos)};
    Vector2 gravity = Vector2Scale(Vector2Normalize(distance), gravity_matrix[this_dot->m_color][other_dot->m_color]*gravity_strenght/Vector2Length(distance));
    Vector2 repel = Vector2Scale(Vector2Normalize(distance), abs(gravity_matrix[this_dot->m_color][other_dot->m_color])*repel_strenght/(Vector2LengthSqr(distance)));
    if(Vector2Length(distance) > gravity_distance)
    {   
        gravity = Vector2Zero();
        repel = Vector2Zero();
    }
    if(Vector2Length(gravity) > max_applied_force) gravity = Vector2Scale(Vector2Normalize(gravity), max_applied_force);    //checking max gravity force
    if(Vector2Length(repel) > max_applied_force) repel = Vector2Scale(Vector2Normalize(repel), max_applied_force);          //checking max repel force

    //use gravity
    if(distance.x != 0 && distance.y != 0)
    {
        this_dot->m_vel = Vector2Subtract(this_dot->m_vel, gravity);
        this_dot->m_vel = Vector2Add(this_dot->m_vel, repel);
    }    
    //std::cout << "distance: " << Vector2Length(distance);
    //std::cout << " gravity: " << Vector2Length(gravity) << std::endl;
}


//basicaly this function calculate gravity or repel strenght based on distance between dots
//its a linear function
//max distance of gravitational field is repel_distance + gravity_distance
//peak repel strenght is at 0 distance
//0 gravity is at crossing of repel_distance and gravity_distance, or in other words 0 gravity is at max repel distance and 0 gravity_distance
//peak gravity strenght is at repel_distnace + gravity_distance/2
//0 gravity is if distance of dots is greater than gravity_distance + repel_distance


void get_gravity_v2(std::shared_ptr<Dot> this_dot, const std::shared_ptr<Dot> other_dot)
{
    //calculating distance
    Vector2 distance_vec = Vector2{Vector2Subtract(this_dot->m_pos,other_dot->m_pos)};  //vector value
    float distance_scal = Vector2Length(distance_vec);                                  //scalar value

    //initializing just direction of the forces
    Vector2 gravity {Vector2Zero()};   
    Vector2 repel {Vector2Zero()};

    //if other dot is in distance of repel force
    if(distance_scal <= repel_distance)
    {
        //linear function: min -repel_strenght at 0, max 0 at repel_distance  
        repel = Vector2Scale(distance_vec, (repel_strenght - repel_strenght / repel_distance * distance_scal)); 
    }
    //if other dot is in distance between repel_distnace and repel_distnace + gravity_distance/2
    if(distance_scal > repel_distance && distance_scal < (repel_distance + gravity_distance/2))
    {
        //linear function : min 0 at repel distance, max gravity_strenght at gravity_distance/2 + repel_distance
        gravity = Vector2Scale(distance_vec, 
            (gravity_matrix[this_dot->m_color][other_dot->m_color]                               // scaling by gravity matrix
            * (distance_scal - repel_distance) * gravity_strenght / gravity_distance * 2));      
        
    }
    //if other dot is in distance between repel_distnace + gravity_distance/2 and repel_distnace + gravity_distance
    if(distance_scal >= (repel_distance + gravity_distance/2) && distance_scal < (repel_distance + gravity_distance))
    {
        //linear function : max gravity_strenght at repel distance + gravity_distance/2, 0 gravity if distance is more than gravity_distance + repel_distance
        gravity = Vector2Scale(distance_vec, 
            gravity_matrix[this_dot->m_color][other_dot->m_color]                               // scaling by gravity matrix
            * (gravity_strenght - gravity_strenght / gravity_distance * 2 * (distance_scal - repel_distance - gravity_distance / 2)));         
    }
    //checking for max gravity field of a dot
    if(distance_scal > (gravity_distance + repel_distance))
    {   
        gravity = Vector2Zero();
        repel = Vector2Zero();
    }

    //limit max gravity strengtht (optional)
    if(Vector2Length(gravity) > max_applied_force) gravity = Vector2Scale(Vector2Normalize(gravity), max_applied_force);    //checking max gravity force
    if(Vector2Length(repel) > max_applied_force) repel = Vector2Scale(Vector2Normalize(repel), max_applied_force);          //checking max repel force

    //apply gravity, check for 0
    if(distance_vec.x != 0 && distance_vec.y != 0)
    {
        this_dot->m_vel = Vector2Subtract(this_dot->m_vel, gravity);
        this_dot->m_vel = Vector2Add(this_dot->m_vel, repel);
    } 

    //std::cout << "distance: " << distance_scal;
    //std::cout << " repel: " << Vector2Length(repel);
    //std::cout << " gravity: " << Vector2Length(gravity) << std::endl;
} 


class World
{
    public:
        void add_dot_on_click()
        {
            all_dots.push_back(std::make_shared<Dot> (Dot{GetMousePosition().x, GetMousePosition().y,0.0f,0.0f}));
        }
        void add_custom_dot(const std::shared_ptr<Dot> & operand)
        {
            all_dots.push_back(operand);
        }
        void add_rand_dot()
        {
            all_dots.push_back(std::make_shared<Dot> (Dot{}));
        }
        void remove_dot()
        {
            all_dots.pop_back();
        }
        std::vector<std::shared_ptr<Dot>> &get_all_dots()
        {
            return all_dots;
        }
        //draw dots include updating position and velocity
        void draw_dots()
        {
            //check all dots with all dots and apply gravity
            for(std::size_t i {0}; i<all_dots.size(); i++)
            {
                for(std::size_t j {0}; j<all_dots.size(); ++j)
                {
                    if(i == j) continue;
                    get_gravity_v2(all_dots[i], all_dots[j]);
                }

            }

            for(std::size_t i {0}; i<all_dots.size(); i++)
            {
            //apply friction to speed
            if(Vector2Length(all_dots[i]->m_vel) > max_speed)
            {
                all_dots[i]->m_vel = Vector2Scale(all_dots[i]->m_vel, friction);
            }
            //update movement
            all_dots[i]->m_pos = Vector2Add(all_dots[i]->m_pos, all_dots[i]->m_vel);
            //draw dots
            DrawCircle(all_dots[i]->m_pos.x, all_dots[i]->m_pos.y, all_dots[i]->m_radius, all_dots[i]->m_color_true);
            }
        }
    private:
        std::vector<std::shared_ptr<Dot>> all_dots {};
};

void bounce_walls(std::vector<std::shared_ptr<Dot>> &all_dots)
{
    for(std::size_t i {0}; i<all_dots.size(); ++i)
    {
        if(all_dots[i]->m_pos.x < 0)
        {
            all_dots[i]->m_pos.x = 0;
            all_dots[i]->m_vel.x *= -1;
        }
        if(all_dots[i]->m_pos.x > screen_w)
        {
            all_dots[i]->m_pos.x = screen_w;
            all_dots[i]->m_vel.x *= -1;
        }
        if(all_dots[i]->m_pos.y < 0)
        {
            all_dots[i]->m_pos.y = 0;
            all_dots[i]->m_vel.y *= -1;
        }
        if(all_dots[i]->m_pos.y > screen_h)
        {
            all_dots[i]->m_pos.y = screen_h;
            all_dots[i]->m_vel.y *= -1;
        }
    }
}

void teleport_walls(std::vector<std::shared_ptr<Dot>> &all_dots)
{
    for(std::size_t i {0}; i<all_dots.size(); ++i)
    {
        if(all_dots[i]->m_pos.x < 0)
        {
            all_dots[i]->m_pos.x = screen_w;
        }
        if(all_dots[i]->m_pos.x > screen_w)
        {
            all_dots[i]->m_pos.x = 0;
        }
        if(all_dots[i]->m_pos.y < 0)
        {
            all_dots[i]->m_pos.y = screen_h;
        }
        if(all_dots[i]->m_pos.y > screen_h)
        {
            all_dots[i]->m_pos.y = 0;

        }
    }
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
    std::shared_ptr<Dot> player_ptr = static_cast<std::shared_ptr<Dot>>(player.get_ptr());
    world.add_custom_dot(player_ptr);


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
        
        //draw_player(player);
        update_player_pos(player);
        world.draw_dots();
        teleport_walls(world.get_all_dots());


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