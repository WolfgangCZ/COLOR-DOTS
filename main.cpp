#include <iostream>
#include "raylib.h"

int main ()
{
    const int screen_width {1600};
    const int screen_height {800};
    InitWindow(screen_width, screen_height, "New window");

//setting up camera
    Vector2 camera_position {screen_width/2,screen_height/2};

    Camera2D camera {0};
    camera.target = camera_position;
    camera.offset = (Vector2){screen_width/2,screen_height/2};
    camera.rotation = 0;
    camera.zoom = 1;


    SetTargetFPS(60);
    while(WindowShouldClose()==false)
    {
        //-------------------------------------------------------------------------------
        //GAME LOGIC
        //-------------------------------------------------------------------------------

        // Camera zoom controls
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);


        EndMode2D();
        EndDrawing();
    }
    std::cout << "DONE! See ya ";
    return 0;
}