#define GL_SILENCE_DEPRECATION

#include "window.hpp"
#include "game.hpp"

//============================================= CREATION ===============================================//

Window::Window()
{
    default_width = 1000;
    default_height = 500;
}

void Window::load() const
{
    int window_position_x = (glutGet(GLUT_SCREEN_WIDTH) - default_width) / 2;
    int window_position_y = (glutGet(GLUT_SCREEN_HEIGHT) - default_height) / 2;
    
    glutInitWindowPosition(window_position_x, window_position_y);
    glutInitWindowSize(default_width, default_height);
    glutCreateWindow("Game_name");
}

//============================================ CALLBACK ================================================//

void Window::reshape(int width, int height)
{
    if (height == 0) {height = 1;}
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(65.0, (width * 1.0)/height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void Window::recenter() const
{
    CGPoint center;
    center.x = glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH) / 2;;
    center.y = glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT) / 2;
    CGWarpMouseCursorPosition(center);
}
