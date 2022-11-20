#pragma once

#include "camera.hpp"
#include "window.hpp"

class Control
{
private:

//    CONSTANTES
    
    static const double JUMP_HEIGHT;
    static const double GRAVITY;
    
//    VARIABLES
    
    int offset_x;
    int offset_y;
    
//    BOUTONS
    
    Vector3D joystick;
    
    bool flick_flashlight;
    bool left_click;
    
//    LEVIERS
    
    bool fullscreen;
    bool airborne;
    bool flashlight;

//    RELATIONS
    
    friend class Game;
    friend class Camera;
    friend class Object;

public :
    
//    CREATION
    
    Control();
    
//    CALLBACKS
    
    static void keyDown(unsigned char, int, int);
    static void keyUp(unsigned char, int, int);
    
    static void pan(int, int);
    static void click(int, int, int, int);
};
