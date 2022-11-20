#define GL_SILENCE_DEPRECATION

#include "game.hpp"

Window Game::window;
Camera Game::camera;
Control Game::control;

void Game::load()
{
    window.load();
    
    Texture::loadAll();
    Model::loadAll();
    Object::loadAll();
    Light::loadAll();
    
}

void Game::run() const
{
//    AFFICHAGE
    
    glutDisplayFunc(Camera::display);
    glutReshapeFunc(window.reshape);
    glutIdleFunc(Camera::display);

//    CONTROLES
    
    glutIgnoreKeyRepeat(1);

    glutKeyboardFunc(Control::keyDown);
    glutKeyboardUpFunc(Control::keyUp);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutPassiveMotionFunc(Control::pan);
    glutMouseFunc(Control::click);
    
//    Z-BUFFER
    
    glEnable(GL_DEPTH_TEST);
    
//    LOOP
    
    glutMainLoop();
}
