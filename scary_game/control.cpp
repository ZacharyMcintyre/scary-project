#define GL_SILENCE_DEPRECATION

#include "control.hpp"
#include "game.hpp"

//=============================================== ETATS ================================================//

const double Control::JUMP_HEIGHT = 3.0;
const double Control::GRAVITY = 0.2;

//============================================= CREATION ===============================================//

Control::Control()
{
    offset_x = glutGet(GLUT_WINDOW_WIDTH) / 2;
    offset_y = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    
    Vector3D next_move;
}

//============================================ CALLBACKS ===============================================//

void Control::keyDown(unsigned char key, int xx, int yy)
{
    switch (key)
    {
        case 'q':
        case 'Q':
            Game::control.joystick.x = -1;
            break;
        case 'd':
        case 'D':
            Game::control.joystick.x = +1;
            break;
        case 'z':
        case 'Z':
            Game::control.joystick.z = +1;
            break;
        case 's':
        case 'S':
            Game::control.joystick.z = -1;
            break;
        case 'f':
        case 'F':
            if (Game::control.fullscreen == false)
            {
                glutFullScreen();
                Game::control.fullscreen = true;
            }
            else
            {
                Game::window.reshape(Game::window.default_width, Game::window.default_height);
                glutReshapeWindow(Game::window.default_width, Game::window.default_height);
                Game::control.fullscreen = false;
            }
            break;
        case 'a':
        case 'A':
            if (Game::control.airborne == false)
            {
                Game::control.airborne = true;
                Game::control.joystick.y += JUMP_HEIGHT;
            }
            break;
        case 27:
            exit(0);
            break;
    }
}

void Control::keyUp(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
        case 'Q':
            if (Game::control.joystick.x == -1) {Game::control.joystick.x = 0.0;}
            break;
        case 'd':
        case 'D':
            if (Game::control.joystick.x == +1) {Game::control.joystick.x = 0.0;}
            break;
        case 'z':
        case 'Z':
            if (Game::control.joystick.z == +1) {Game::control.joystick.z = 0.0;}
            break;
        case 's':
        case 'S':
            if (Game::control.joystick.z == -1) {Game::control.joystick.z = 0.0;}
            break;
    }
}

void Control::pan(int x, int y)
{
    if (x <= 0 || y <= 0 || x >= glutGet(GLUT_WINDOW_WIDTH) || y >= glutGet(GLUT_WINDOW_HEIGHT))
    {
        Game::window.recenter();
        Game::control.offset_x = glutGet(GLUT_WINDOW_WIDTH) / 2; Game::control.offset_y = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    }
    else if (x != Game::control.offset_x || y != Game::control.offset_y)
    {
        Game::camera.turn(x - Game::control.offset_x, Game::control.offset_y - y);
        Game::control.offset_x = x; Game::control.offset_y = y;
    }
}

void Control::click(int button, int state, int x, int y)
{
   if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && Game::control.flashlight && Game::control.flick_flashlight == false)
   {
       glEnable(GL_LIGHT3);
       Game::control.flick_flashlight = true;
   }
   else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && Game::control.flick_flashlight == true)
   {
       glDisable(GL_LIGHT3);
       Game::control.flick_flashlight = false;
   }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Game::camera.select();
    }
}
