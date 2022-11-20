#pragma once

#include "vertex.hpp"
#include "material.hpp"

class Model
{
private:
    
//    DONNEES
    
    string name;
    vector<Vertex> vertices;
    
//    STOCKAGE
    
    static vector<Model> models;
    
//    RELATIONS
    
    friend class Game;
    friend class Object;
    friend class Camera;
    
public:
    
//    CHARGEMENT
    
    Model(const string);
    static void loadAll();
    
//    DESSIN
    
    void draw() const;
};
    
