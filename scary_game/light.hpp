#pragma once

#include "object.hpp"

class Light
{
private:
    
    friend class Game;
    friend class Camera;
    
public:
    
//    CHARGEMENT
    
    static void loadAll();
    
//    TEMPS REEL
    
    static void setAll();
};
