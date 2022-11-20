#pragma once

#include "vector3D.hpp"
#include "texture.hpp"

class Material
{
    private :
    
//    DONNEES
    
    string name;
    
    double specular_exponent;
    double optic_density;
    double transparence;
    
    Vector3D ambient_color;
    Vector3D diffuse_color;
    Vector3D specular_color;
    Vector3D emissive_color;
    
    int light_parameters;
    
    int texture_id;
    Vector3D texture_scale;
    
//    STOCKAGE
    
    static vector<Material> materials;
    
//    RELATIONS
    
    friend class Model;
    friend class Object;
    friend class Vertex;
    
public:
    
//    CHARGEMENT
    
    Material(string);
    static void loadAll(const string);
    
//    MISE EN PLACE
    
    void bind();
    
//    AUTRES
    
    static bool brandNew(const string);
    static int find(const string);
};

