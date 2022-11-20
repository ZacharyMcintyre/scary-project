#pragma once

#include "vector3D.hpp"

class Window
{
private :
    
//    PARAMETRES PAR DEFAUT
    
    int default_width;
    int default_height;
    
//    RELATIONS
    
    friend class Control;
    
public:
    
//    CREATION
    
    Window();
    void load() const;
    
//    CALLBACK
    
    static void reshape(int, int);
    void recenter() const;
};
