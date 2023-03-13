#include<cmath>
#include<algorithm>
#include<cassert>
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
float calculate_angle_xy(float x, float y)
{
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
float get_gravity(float distance)
{        
    //wonky equation for calculating gravity its just line on y axis from -1 to 1 and then back on 0 and 1,2,3 on x axis multiplies by gravity_threshold
    //i know its bad to have two completely same equations with 1 and -1 but i didnt figure out better way on the spot now...
    //i fix it later
    //btw with this wonky formula the distance is actually 3/4 of actual distance :-/
    //rework all this / negative value must be fixed! 
    if(distance<0) 
    {
        distance *= -1;

        if(distance <= gravity_threshold/2)
        {
            return -1*(distance-gravity_threshold/4)*gravity_modifier;
        }
        else if (distance > gravity_threshold/2 && distance < gravity_threshold/4*3)
        {
            return -1*(gravity_threshold/4*3-distance)*gravity_modifier;
        }
        else if (distance >= gravity_threshold/4*3) return 0;
    }
    else 
    {
        if(distance <= gravity_threshold/2)
        {
            return (distance-gravity_threshold/4)*gravity_modifier;
        }
        else if (distance > gravity_threshold/2 && distance < gravity_threshold/4*3)
        {
            return (gravity_threshold/4*3-distance)*gravity_modifier;
        }
        else if (distance >= gravity_threshold/4*3) return 0;
    }
    return 0;
}
float friction_calc(float friction, float velocity)
{   
    return -(velocity*friction);
}

