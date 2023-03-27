#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

extern const std::size_t screen_w{800};
extern const std::size_t screen_h{600};
extern const std::size_t starting_dots {400};
extern const float player_speed {0.5};
extern const float friction {0.95};
extern const float max_applied_force {1};

extern const float repel_distance {200};
extern const float gravity_distance {200};

extern const float gravity_strenght {4};
extern const float repel_strenght {100};

float gravity_matrix [7][7]
    {
        //upper right - row repel column
        {1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0},  //GRAY
        {0.0, -1.0, 0.5, 0.0, 0.0, 0.0, 0.0},  //RED
        {0.0, -1.0, 1.0, 0.5, 0.0, 0.0, 0.0},  //GOLD
        {0.0, -1.0, 0.0, 1.0, 0.5, 0.0, 0.0},  //LIME
        {0.0, -1.0, 0.0, 0.0, 1.0, 0.5, 0.0},  //BLUE
        {0.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.5},  //VIOLET
        {0.5, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0}   //BROWN
        //lower left - column repel row
    };


#endif //GLOBAL_VAR_H