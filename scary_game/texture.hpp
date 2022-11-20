#pragma once

#include "vector3D.hpp"

using namespace std;

class Texture
{
private :
    
//    STOCKAGE
    
    static vector<Texture> textures;
    
//    DONNEES
    
    string name;
    GLuint id;
    int width, height;
    
//    RELATIONS
    
    friend class Model;
    friend class Game;
    friend class Object;
    friend class World;
    friend class Material;
    friend class Vertex;
    
public :
    
//    CHARGEMENT
    
    Texture(const string);
    void static loadAll();
    
//    MISE EN PLACE
    
    void bind();
};
