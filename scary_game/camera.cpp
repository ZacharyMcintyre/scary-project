#define GL_SILENCE_DEPRECATION

#include "camera.hpp"
#include "game.hpp"

//============================================== CREATION ================================================//

Camera::Camera()
{
    height = 1.0;
    speed = 0.1;
    rate = 0.005;
    
    hitbox = Vector3D(0.25, height * 2, 0.25);
    
    position = Vector3D(0.0, height, 0.0);
    orientation = Vector3D(0.0, 0.0, 1.0);
    
    forward = orientation; forward.y = 0.0; forward.normalize();
    up = Vector3D(0.0, 1.0, 0.0);
    right = forward.cross(up);
}

//============================================= DEPLACEMENT ==============================================//

bool Camera::collision(const double a, const double b, const double c, const int i)
{
    return (abs(a - Object::objects[i].position.x) < (Object::objects[i].hitbox.x + hitbox.x) / 2.0 &&
            abs(b - Object::objects[i].position.y) < (Object::objects[i].hitbox.y + hitbox.y) / 2.0 &&
            abs(c - Object::objects[i].position.z) < (Object::objects[i].hitbox.z + hitbox.z) / 2.0);
}

void Camera::physics()
{
    Game::control.airborne = true;
    
//    GRAVITE
        
    if (Game::control.airborne == true)
    {
        Game::control.joystick.y -= Game::control.GRAVITY;
    }
    
//    COLLISIONS
    
    step = Game::control.joystick.z * forward * speed + Game::control.joystick.y * up * speed + Game::control.joystick.x * right * speed;
    
    for (int i = 0; i < Object::objects.size(); i++)
    {
        if (collision(position.x + step.x, position.y + step.y, position.z + step.z, i))
        {
            if (collision(position.x + step.x, position.y, position.z, i))
            {
                step.x = 0;
            }
            if (collision(position.x + step.x, position.y, position.z + step.z, i))
            {
                step.z = 0;
            }
            if (collision(position.x + step.x, position.y + step.y, position.z + step.z, i))
            {
                step.y = 0;
                Game::control.airborne = false;
                Game::control.joystick.y = 0;
            }
        }
    }
}

//void Camera::collisions()
//{
//    for (int i = 0; )
//}

void Camera::move()
{
    position += step;
}

void Camera::turn(const int dx, const int dy)
{
    orientation = (orientation+ (right * dx + up * dy) * rate).normalize();
    right = orientation.cross(up);
    forward = orientation; forward.y = 0.0; forward.normalize();
}


void Camera::shoot() const
{
    gluLookAt(position.x, position.y, position.z, (position + orientation).x, (position + orientation).y, (position + orientation).z, up.x, up.y, up.z);
}

void Camera::select() const
{
    int min_id = -1; double min = 5;
    
    for (int i = 0; i < Object::objects.size(); i++)
    {
        if (Object::objects[i].selectable == true)
        {
            //mettre dans Vector3D
            double distance_to_cursor = (Object::objects[i].position-position-orientation*orientation.scalar(Object::objects[i].position-position)).length();
            double distance_to_player = (Object::objects[i].position - position).length();
            
            if (distance_to_cursor < 0.3 && distance_to_player < min)
            {
                min_id = i; min = distance_to_player;
            }
        }
    }
    if (min_id != -1)
    {
        Object::objects[min_id].selected = true;
    }
}

//=============================================== CALLBACK =================================================//

void Camera::display()
{
    Game::camera.physics();
    Game::camera.move();
    
    Light::setAll();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    Game::camera.shoot();
    Object::drawAll();
    
    glutSwapBuffers();
}
