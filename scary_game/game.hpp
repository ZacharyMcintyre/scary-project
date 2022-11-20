#pragma once

#include "control.hpp"
#include "light.hpp"
#include "texture.hpp"
#include "object.hpp"

class Game
{
private :
    
    static Window window;
    static Camera camera;
    static Control control;
    
    friend class Control;
    friend class Camera;
    friend class Model;
    friend class Object;
    friend class Vertex;
    friend class Window;
    friend class Light;
    
public:
    
    void load();
    void run() const;
};
