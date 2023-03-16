#include <cmath>
#include <vector>

#include <rigidbody/vector3d.hpp>


namespace rigidbody
{

class RigidBody_c
{
protected:
    float Mass;

    Vector3D_s Position;
    Vector3D_s Velocity;
    Vector3D_s Acceleration;

    std::vector<Vector3D_s> Forces;

public:
    Vector3D_s position() const
    {
        return Position;
    }

    Vector3D_s velocity() const
    {
        return Velocity;
    }

    void addForce(Vector3D_s force)
    {
        Forces.push_back(force);
    }

    void update(float delta_time)
    {
        // Calculate total force acting on the rigid body
        Vector3D_s total_force(0, 0, 0);
        for (Vector3D_s& force : Forces)
        {
            total_force = total_force + force;
        }

        // Calculate acceleration from force and mass
        Acceleration = total_force / Mass;

        // Update velocity and position using acceleration
        Velocity = Velocity + Acceleration * delta_time;
        Position = Position + Velocity * delta_time;

        // Clear forces for next frame
        Forces.clear();
    }

    RigidBody_c(Vector3D_s position, Vector3D_s velocity, float mass) :
        Mass(mass),
        Position(position),
        Velocity(velocity)
    {}
};

} // namespace rigidbody