#pragma once

#include "model.hpp"

class Object
{
protected :
    
//    DONNEES
    
    const Model* model;
    
    Vector3D position;
    Vector3D color;
    Vector3D angles;
    Vector3D scale;
    
//    COORDONNEES LOCALES
    
    Vector3D Ox, Oy, Oz;
    
//    PROPRIETES
    
    bool collisions; Vector3D hitbox;
    bool always_visible;
    bool selectable;
    
//    ETATS
    
    bool selected;
    
//    STOCKAGE
    
    static vector<Object> objects;
    
//    RELATIONS
    
    friend class Game;
    friend class Camera;
    
public :
    
    Object(const Model *);
    
//    CHARGEMENT
    
    static void loadAll();
    static void load(const Model*);
    
//    MISE EN PLACE
        
    static void setCursor();
    void setFlashlight();
    void setGround();
    
//    DESSIN
    
    static void drawAll();
    void set();
    void draw();
};

class Ground : public Object
{
    public :
    
    Ground(const Model*, const int);
};

class Tree : public Object
{
    public :
    
    Tree(const Model *);
};

class Sky : public Object
{
    public :
    
    Sky(const Model *);
};

class Rock : public Object
{
    public :
    
    Rock(const Model *);
};

class Flashlight : public Object
{
    public :
    
    Flashlight(const Model *);
};

class Pillar : public Object
{
    public :
    
    Pillar(const Model *, const int);
};
