#ifndef UTILITIES_H
#define UTILITIES_H

/*
some math and physics calculations so far to ease things up
*/

//compute x and y value from orto value lenght and angle
float calculate_x_from_orto(float lenght, float angle_rads);
float calculate_y_from_orto(float lenght, float angle_rads);
float calculate_from_orto(float lenght, float angle);
float calculate_from_orto(float lenght, float angle);
float calculate_orto_lenght(float x, float y);
float calculate_angle_xy(float x, float y);

float degrees_to_rads(float value);
float rads_to_degrees(float value);

//add function for gravity - sometihng like y=-(x2)+1 that should do it
float get_repel(float distance);
float get_gravity(float distance);


//compute friction and retrun value for substracting from velocity
//ADD weight component and maybe terrain component for dynamic friction on map
float friction_calc(float friction, float velocity);


Color get_color (int number);

#endif //UTILITES_H