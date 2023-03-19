#include<cmath>
#include<algorithm>
#include<cassert>
#include<cmath>
#include<iostream>

#include "global_variables.h"
#include "raylib.h"
#include "utilities.h"


float calculate_x_from_orto(float lenght, float angle_rads)
{
    return std::sin(angle_rads)*lenght;
}
float calculate_y_from_orto(float lenght, float angle_rads)  //
{
    return std::cos(angle_rads)*lenght;
}
float calculate_orto_lenght(float x, float y)
{
    return std::sqrt(x*x+y*y);
}
//!!!!!!!!!!!!!!!!!!!!!!!!
//rework for coordinates of raylib window!!!!!!
float calculate_angle_xy(float x, float y)
{
    x *= -1; //is it correct?
    if(x == 0 && y == 0)        
    {
        return 0;
    } 
    else if(x >= 0 && y >= 0)   //right upper
    {
        if (x==0) return 0;
        else if (y==0) return PI/2;
        return std::abs(std::atan(x/y));
    }
    else if(x >= 0 && y <= 0)   //right bottom
    {
        if (x==0) return PI;
        else if (y==0) return PI/2;
        return PI - std::abs(std::atan(x/y));
    }
    else if(x <= 0 && y <= 0)   //left bottom
    {
        if (x==0) return PI;
        else if (y==0) return PI+PI/2;
        return PI + std::abs(std::atan(x/y));
    }
    else if(x <= 0 && y >= 0)   //left upper
    {
        if (x==0) return 0;
        else if(y ==0 ) return PI + PI/2;
        return 2*PI-std::abs(std::atan(x/y));
    }
    return 0;
}

float degrees_to_rads(float value)
{
    return value/180*PI;
}
float rads_to_degrees(float value)
{
    return value*180/PI;
}


//its not caluclating for negative values (or maybe it does?) no it doesnt
//split this function in two!!!
/*
float get_gravity(float distance)
{        
    int dir_mod; 
    if(distance<0) dir_mod = -1;
    else if (distance>0) dir_mod = 1;        
    distance = abs(distance);
    if(distance <= repel_distance)
        return -dir_mod*(distance-repel_distance)*repel_modifier;

    else if (distance > repel_distance && distance < (gravity_distance/2+repel_distance))
        return dir_mod*(distance*20/gravity_distance-repel_distance*20/gravity_distance)*gravity_modifier;

    else if (distance >= (gravity_distance/2+repel_distance) && distance < (gravity_distance+repel_distance)) 
        return dir_mod*(gravity_distance/2+repel_distance*2-distance)*gravity_modifier;
    else return 0;
}
*/
//better calculation

float get_repel(float distance)
{
if(distance <= repel_distance)
    return (distance-repel_distance)*repel_modifier;
return 0;
}

float get_gravity(float distance)
{            
    if (distance > repel_distance && distance < (gravity_distance/2+repel_distance))
        return (distance*20/gravity_distance-repel_distance*20/gravity_distance)*gravity_modifier;

    else if (distance >= (gravity_distance/2+repel_distance) && distance < (gravity_distance+repel_distance)) 
        return (gravity_distance/2+repel_distance*2-distance)*gravity_modifier;
    else return 0;
}

float friction_calc(float friction, float velocity)
{   
    return -(velocity*friction);
}

