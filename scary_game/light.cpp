#define GL_SILENCE_DEPRECATION

#include "light.hpp"
#include "game.hpp"

void Light::loadAll()
{
    glEnable(GL_LIGHTING);
    glShadeModel (GL_SMOOTH);
    
//    LUNE
    
    GLfloat diffuse_color_1[] = {2.0, 2.0, 2.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_color_1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 70.0);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 5);
    
    glEnable(GL_LIGHT1);
    
//    ACUITE
    
    GLfloat diffuse_color_2[] = {4.0, 4.0, 4.0, 1.0 };
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_color_2);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.01);
    
    glEnable(GL_LIGHT2);
    
//    TORCHE
    
    GLfloat diffuse_color_3[] = {8.0, 8.0, 8.0, 1.0 };
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse_color_3);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.005);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 5);
}

void Light::setAll()
{
//    LUNE
    
    GLfloat light_position_1[] = { 0.0, 10, 0.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
    GLfloat light_direction_1[] = { 0.0, 1.0, 0.0};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction_1);
    
//    ACUITE
    
    GLfloat light_position_2[] = {(GLfloat) Game::camera.position.x, (GLfloat) Game::camera.position.y, (GLfloat) Game::camera.position.z, 1.0 };
    glLightfv(GL_LIGHT2, GL_POSITION, light_position_2);
    
//    TORCHE
    
    GLfloat light_direction_3[] = {(GLfloat) Game::camera.orientation.x, (GLfloat) Game::camera.orientation.y, (GLfloat) Game::camera.orientation.z};
    glLightfv(GL_LIGHT3, GL_POSITION, light_position_2);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_direction_3);
}
