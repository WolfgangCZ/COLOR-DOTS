#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLE S_H

const int screen_width {800};
const int screen_height {800};
const float gravity_modifier {0.01};
const float dot_radius {2};
const float max_velocity {2};
const float friction {0.9};
const float gravity_threshold {100};
const float wall_bounciness {1};
const float gravity_matrix [7][7]
    {
        {1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0},  //GRAY
        {0.0, 1.0, 0.5, 0.0, 0.0, 0.0, 0.0},  //RED
        {0.0, 0.0, 1.0, 0.5, 0.0, 0.0, 0.0},  //GOLD
        {0.0, 0.0, 0.0, 1.0, 0.5, 0.0, 0.0},  //LIME
        {0.0, 0.0, 0.0, 0.0, 1.0, 0.5, 0.0},  //BLUE
        {0.0, 0.8, 0.0, 0.0, 0.0, 1.0, 0.5},  //VIOLET
        {0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}   //BROWN
    };

#endif //GLOBAL_VARIABLES_H