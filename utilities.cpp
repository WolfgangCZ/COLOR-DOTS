#include<cmath>
#include<algorithm>

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


float friction_calc(float friction, float velocity)
{   
    return -(velocity*friction);
}

