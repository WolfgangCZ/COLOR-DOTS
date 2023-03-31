#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

extern const std::size_t screen_w{800};
extern const std::size_t screen_h{600};
extern const std::size_t starting_dots {500};
extern const float player_speed {0.2};
extern const float friction {0.7};
extern const float max_applied_force {1000};
extern const float max_speed {2};

extern const float repel_distance {20};
extern const float gravity_distance {100};

extern const float gravity_strenght {0.01};
extern const float repel_strenght {0.01};

float gravity_matrix [7][7]
    {
        //upper right - row repel column
        {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},  //GRAY
        {-1.0, 1.0, 0.5, 0.0, 0.0, 0.0, 0.0}, //RED
        {-1.0, 0.0, 1.0, 0.5, 0.0, -1.0, 0.0},  //GOLD
        {-1.0, 0.0, 1.0, 1.0, -1.5, 0.0, 0.0},  //LIME
        {-1.0, 0.0, -1.0, 0.0, 1.0, 0.5, 0.0},  //BLUE
        {-1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.5},  //VIOLET
        {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}   //BROWN
        //lower left - column repel row
    };

    
Color get_color_from_number(size_t selected_color)
{
    //std::cout << "inside get color" << std::endl;
    switch (selected_color)
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


#endif //GLOBAL_VAR_H