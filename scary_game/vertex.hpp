#pragma once

#include "vector3D.hpp"
#include "material.hpp"

class Vertex
{
private:
    
//    DONNEES
    
    int material_id;
    
    Vector3D position;
    Vector3D pixel;
    Vector3D normal;
    
//    RELATIONS
    
    friend class Model;
    friend class Object;
    
public:
    
    void draw() const;
};
