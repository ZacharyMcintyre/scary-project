#pragma once

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <Carbon/Carbon.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Vector3D
{
private:

//    COORDONNES
    
    double x;
    double y;
    double z;
    
//    RELATIONS
    
    friend class Camera;
    friend class Object;
    friend class Control;
    friend class Game;
    friend class Vertex;
    friend class Light;
    friend class Material;

public:
    
//    CREATION
    
    Vector3D();
    Vector3D(double, double, double);
    Vector3D(const Vector3D&);
    Vector3D(const Vector3D&, const Vector3D&);

//    OPERATIONS
    
    Vector3D & operator = (const Vector3D&);

    Vector3D & operator += (const Vector3D&);
    Vector3D operator + (const Vector3D&) const;

    Vector3D & operator -= (const Vector3D&);
    Vector3D operator - (const Vector3D&) const;

    Vector3D & operator *= (const double);
    Vector3D operator * (const double) const;
    friend Vector3D operator * (const double,const Vector3D&);

    Vector3D & operator /= (const double);
    Vector3D operator / (const double) const;
    
    Vector3D cross(const Vector3D &) const;
    double scalar(const Vector3D &) const;
    double length()const;
    Vector3D & normalize();
    
//    DEBUG
    
    friend ostream& operator<<(ostream& os, Vector3D const & v) {
        return os << "("<<v.x<<","<<v.y<<","<<v.z<<")" << endl;
    }
};

