#pragma once

#include "vector3D.hpp"

class Camera
{
private :
    
//    POSITION 6D
        
    Vector3D position;
    Vector3D orientation;
    
//    PARAMETRES
        
    double height;
    double speed;
    double rate;
    Vector3D hitbox;
    
//    COORDONNEES CYLINDRIQUES
    
    Vector3D forward;
    Vector3D up;
    Vector3D right;
    
//    DEPLACEMENT
    
    Vector3D step;
    
//    RELATIONS
    
    friend class Game;
    friend class Object;
    friend class Vertex;
    friend class Light;
    
public:

//    CHARGEMENT
    
    Camera();
    
//    ACTIONS
    
    void move();
    void turn(const int, const int);
    void shoot() const;
    void select() const;
    
//    PHYSIQUE
    
    bool collision(const double, const double, const double, const int);
    void physics();
    
//    CALLBACK
    
    static void display();
};
