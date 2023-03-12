#include <cmath>
#include "physics_model.h"
#include "raylib.h"
#include "utilities.h"

/*

*/

        //getters
        float PhysicsModel::get_velocity()
        {
            return m_velocity;
        }
        float PhysicsModel::get_direction()
        {
            return m_direction; //in rads
        }
        float PhysicsModel::get_rot_velocity()
        {
            return m_rot_velocity;
        }
        float PhysicsModel::get_acc()
        {
            return m_acceleration;
        }
        float PhysicsModel::get_rot_acc()
        {
            return m_rot_acc;
        }

        //getters
        void PhysicsModel::set_velocity(float velocity)
        {
            m_velocity = velocity;
        }
        void PhysicsModel::set_velocity(float x, float y)
        {
            m_velocity = std::sqrt(x*x+y*y);
        }
        void PhysicsModel::set_direction(float angle)
        {
            m_direction = angle;
        }
        void PhysicsModel::set_direction(float x, float y)
        {
            m_direction = calculate_angle_xy(x,y);
        }
        void PhysicsModel::set_acc(float acceleration)
        {
            m_acceleration = acceleration;
        }   
        void PhysicsModel::set_acc(float force, float weight)
        {
            m_acceleration = force/weight;
        }   
        void PhysicsModel::set_rot_velocity(float rot_velocity)
        {
            m_rot_velocity = rot_velocity;
        }
        void PhysicsModel::set_rot_acc(float rot_acc)
        {
            m_rot_acc = rot_acc;
        }
        void PhysicsModel::set_rot_acc(float rot_force, float weight)
        {
            m_rot_acc = rot_force/weight;
        }

        //adders-substractors
        void PhysicsModel::add_velocity(float velocity)
        {
            m_velocity += velocity;
        }
        void PhysicsModel::add_direction(float angle)
        {
            m_direction += angle;
        }
        void PhysicsModel::add_rot_velocity(float rot_velocity)
        {
            m_rot_velocity += rot_velocity;
        }

        //acceleration

