#pragma once

namespace rigidbody
{

/////////////////////////////////////////////////////////////////////////////////////////
// 3D vector type to be used with the RigidBody class

struct Vector3D_s
{
    float X;
    float Y;
    float Z;

    Vector3D_s() :
        X(0.F), Y(0.F), Z(0.F)
    {}

    Vector3D_s(float x, float y, float z) :
        X(x), Y(y), Z(z)
    {}

    inline Vector3D_s operator+ (const Vector3D_s& v) const
    {
        return Vector3D_s(X + v.X, Y + v.Y, Z + v.Z);
    }

    inline Vector3D_s operator- (const Vector3D_s& v) const
    {
        return Vector3D_s(X - v.X, Y - v.Y, Z - v.Z);
    }

    inline Vector3D_s operator* (float s) const
    {
        return Vector3D_s(X * s, Y * s, Z * s);
    }

    inline Vector3D_s operator/ (float s) const
    {
        return Vector3D_s(X / s, Y / s, Z / s);
    }

    inline float dot(const Vector3D_s& v) const
    {
        return X * v.X + Y * v.Y + Z * v.Z;
    }

    inline Vector3D_s cross(const Vector3D_s& v) const
    {
        return Vector3D_s(Y * v.Z - Z * v.Y, Z * v.X - X * v.Z, X * v.Y - Y * v.X);
    }

    inline float magnitude() const
    {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    inline Vector3D_s normalize() const
    {
        Vector3D_s ret = *this;

        float len = magnitude();
        if (len > 0.F)
        {
            ret.X /= len;
            ret.Y /= len;
            ret.Z /= len;
        }

        return ret;
    }
};

} //namespace rigidbody
