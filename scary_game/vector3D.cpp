#include "vector3d.hpp"

#include <cmath>

//=============================================== CREATION ===============================================//

Vector3D::Vector3D()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3D::Vector3D(double a,double b,double c)
{
    x = a;
    y = b;
    z = c;
}

Vector3D::Vector3D(const Vector3D & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3D::Vector3D(const Vector3D & from,const Vector3D & to)
{
    x = to.x - from.x;
    y = to.y - from.y;
    z = to.z - from.z;
}

//============================================== OPERATIONS ==============================================//

Vector3D & Vector3D::operator= (const Vector3D & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vector3D & Vector3D::operator+= (const Vector3D & v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3D Vector3D::operator+ (const Vector3D & v) const
{
    Vector3D t = *this;
    t += v;
    return t;
}

Vector3D & Vector3D::operator-= (const Vector3D & v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3D Vector3D::operator- (const Vector3D & v) const
{
    Vector3D t = *this;
    t -= v;
    return t;
}

Vector3D & Vector3D::operator*= (const double a)
{
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

Vector3D Vector3D::operator* (const double a)const
{
    Vector3D t = *this;
    t *= a;
    return t;
}

Vector3D operator* (const double a,const Vector3D & v)
{
    return Vector3D(v.x*a,v.y*a,v.z*a);
}

Vector3D & Vector3D::operator/= (const double a)
{
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

Vector3D Vector3D::operator/ (const double a)const
{
    Vector3D t = *this;
    t /= a;
    return t;
}

Vector3D Vector3D::cross(const Vector3D & v)const
{
    Vector3D t;
    t.x = y*v.z - z*v.y;
    t.y = z*v.x - x*v.z;
    t.z = x*v.y - y*v.x;
    return t;
}

double Vector3D::scalar(const Vector3D& v) const
{
    return x*v.x + y*v.y + z*v.z;
}

double Vector3D::length()const
{
    return sqrt( x*x + y*y + z*z);
}

Vector3D & Vector3D::normalize()
{
    (*this) /= length();
    return (*this);
}
