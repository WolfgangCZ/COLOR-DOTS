#ifndef PHYSICS_MODEL_H
#define PHYSICS_MODEL_H
#include "raylib.h"

/*
class for store physics model, which are gonna be all physics parametrs (excluding factual position and rotation)

so far parameters 
    - velocity(+ forward,- backward)
    - rotation (+ right, - left), rotation is stored as rads, not degrees!
    - weight (which is just area)

i should probably somehow move weight here i guess to be correct about physics, maybe even position and rotation? 
that could be hard to move cause position, rotation and weight is tightly tied to structure i guess(LOOK INTO IT)

MODIFY direction rename to angle to better clarity i guess (angle is in rads as default)
*/

class PhysicsModel
{
    public:
        PhysicsModel()
        {}
        ~PhysicsModel()
        {}
        //getters
        float get_velocity();
        float get_direction();
        float get_rot_velocity();
        float get_acc();
        float get_rot_acc();

        //setters
        //setting by exact number or force * weight
        void set_velocity(float velocity);
        void set_velocity(float x, float y);

        void set_direction(float angle);
        void set_direction(float x, float y);

        void set_acc(float acceleration);
        void set_acc(float force, float weight);
        
        void set_rot_velocity(float rot_velocity);      
        void set_rot_acc(float rot_acc);
        void set_rot_acc(float rot_force, float weight);

        //adders-substractors
        void add_velocity(float velocity);
        void add_direction(float angle);
        void add_rot_velocity(float rot_velocity);

        //functions

    protected:
        float m_direction {0}; //facing up, rad
        float m_velocity {0};
        float m_rot_velocity {0};
        float m_acceleration {0};
        float m_rot_acc{0};
};

#endif //PHYSICS_MODEL_H