#define GL_SILENCE_DEPRECATION

#include "object.hpp"
#include "game.hpp"

vector<Object> Object::objects;

Object::Object(const Model* model)
{
    this->model = model;
    selected = false;
}

void Object::loadAll()
{
    for (int i = 0; i < Model::models.size(); i++)
    {
        load(Model::models[i]);
    }
}

void Object::load(Model model)
{
    if (model.name == "ground")
    {
        for (int j = 0; j < 4; j++)
        {
            Ground ground(&model, j);
            objects.push_back(ground);
        }
    }
    if (model.name == "sky")
    {
        Sky sky(&model);
        objects.push_back(sky);
    }
    if (model.name == "dead_tree")
    {
        for (int j = 0; j < 10000; j++)
        {
            Tree tree(&model);
            objects.push_back(tree);
        }
    }
    if (model.name == "rock")
    {
        for (int j = 0; j < 1000; j++)
        {
            Rock rock(&model);
            objects.push_back(rock);
        }
    }
    if (model.name == "flashlight")
    {
        Flashlight flashlight(&model);
        objects.push_back(flashlight);
    }
    if (model.name == "pillar")
    {
        for (int j = 0; j < 5; j++)
        {
            Pillar pillar(&model, j);
            objects.push_back(pillar);
        }
    }
}

void Object::drawAll()
{
    //curseur temporaire
    setCursor();
    for (int i = 0; i < objects.size(); i++)
    {
        if ((objects[i].position - Game::camera.position).length() < 50 || objects[i].always_visible)
        {
            if (objects[i].model->name == "ground")
            {
                objects[i].setGround();
            }
            else if (objects[i].model->name == "flashlight")
            {
                objects[i].setFlashlight();
            }
            glPushMatrix();
            objects[i].set();
            objects[i].model->draw();
            glPopMatrix();
        }
    }
}

void Object::setFlashlight()
{
//    PRISE EN MAIN
    
    if (selected)
    {
        Game::control.flashlight = true;
        
        position = Game::camera.position - 0.3 * Game::camera.right + 0.5 * Game::camera.orientation - 0.2 * Game::camera.up;
        angles.y = acos(Vector3D(0.0, 0.0, -1.0).scalar(Game::camera.orientation)) * 180/3.14;
        angles.x = acos(Vector3D(0.0, 0.0, -1.0).scalar(Game::camera.orientation)) * 180/3.14;

    }
    
//    FAISCEAU
    
    if (Game::control.flashlight == false || Game::control.flick_flashlight == true)
    {
        glPushMatrix();
                
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
                
        glColor4f(1.0f, 1.0f, 0.3f, 0.2);
        glTranslatef(position.x, position.y, position.z);
        glRotatef(angles.y, 0.0, 1.0, 0.0);
        glTranslatef(0.0, 0.0, 0.5 - 1.5);
        
        glutSolidCone(0.2, 1.5, 20, 20);
                
        glDisable(GL_BLEND);
                
        glPopMatrix();
    }
}

void Object::setCursor()
{
    glPushMatrix();
            
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glTranslatef(Game::camera.position.x, Game::camera.position.y, Game::camera.position.z);
    glTranslatef(Game::camera.orientation.x, Game::camera.orientation.y, Game::camera.orientation.z);
    glutSolidCube(0.005);
    
    glPopMatrix();
}

void Object::setGround()
{
    if (Game::camera.position.x - position.x > 50)
    {
        position.x += 100;
    }
    else if (Game::camera.position.x - position.x < -50)
    {
        position.x -= 100;
    }
    if (Game::camera.position.z - position.z > 50)
    {
        position.z += 100;
    }
    else if (Game::camera.position.z - position.z < -50)
    {
        position.z -= 100;
    }
}


void Object::set()
{
    glTranslatef(position.x,position.y,position.z);
    
    glRotatef(angles.x, 1.0, 0.0, 0.0);
    glRotatef(angles.y, 0.0, 1.0, 0.0);
    glRotatef(angles.z, 0.0, 0.0, 1.0);
    
    glScalef(scale.x, scale.y, scale.z);
    
    glColor3f(color.x, color.y, color.z);
}

Ground::Ground(const Model* model, const int j) : Object(model)
{
    position = Vector3D(-25.0 + (j/2) * 50, 0.0, -25.0 + (j%2) * 50);
    color = Vector3D(1.0, 1.0, 1.0);
    scale = Vector3D(1.0,1.0,1.0);
    hitbox = Vector3D(100.0,0.0,100.0);

    always_visible = true;
}

Tree::Tree(const Model* model) : Object(model)
{
    int a = rand() % 1000 - 500;
    int b = rand() % 1000 - 500;
    
    while (abs(a) < 5 && abs(b) < 5)
    {
        a = rand() % 1000 - 500;
        b = rand() % 1000 - 500;
    }
    
    position = Vector3D(a, 0.0, b);
    color = Vector3D(1.0, 1.0, 1.0);
    scale = Vector3D(5.0, 2.0 + (rand() % 100) * 0.06, 5.0);
    hitbox = Vector3D(2.0, 10, 2.0);
    
    angles = Vector3D(0.0, rand() % 360, 0.0);
}

Sky::Sky(const Model* model) : Object(model)
{
    position = Vector3D(0.0, 0.0, 0.0);
    color = Vector3D(1.0, 1.0, 1.0);
    scale = Vector3D(5.0,5.0,5.0);
    hitbox = Vector3D(-100.0,-100.0,-100.0); //collisions désactivées
    
    always_visible = true;
}

Rock::Rock(const Model* model) : Object(model)
{
    position = Vector3D(rand() % 1000 - 500, 0.0, rand() % 1000 - 500);
    color = Vector3D(1.0, 1.0, 1.0);
    scale = Vector3D(2.0 + (rand() % 100) * 0.03, 2.0 + (rand() % 100) * 0.03, 2.0 + (rand() % 100) * 0.03);
    hitbox = Vector3D(2.0, 2, 2.0);
    
    angles = Vector3D(0.0, rand() % 360, 0.0);
}

Flashlight::Flashlight(const Model * model) : Object(model)
{
    position = Vector3D(0.0, 0.05, 2.0);
    color = Vector3D(0.8, 0.8, 0.8);
    scale = Vector3D(2.0,2.0,2.0);
    hitbox = Vector3D(-100.0, -100.0, -100.0);
    
    angles = Vector3D(0.0, rand() % 360, 0.0);
    
    selectable = true;
}

Pillar::Pillar(const Model* model, const int j) : Object(model)
{
    position = Vector3D(3 * cos(2*3.14*j/5), -3+0.75*j, 3*sin(2*3.14*j/5));
    color = Vector3D(0.2, 0.2, 0.2);
    scale = Vector3D(2.0,2.2,2.0);
    hitbox = Vector3D(1.75, 9, 1.75);

    angles = Vector3D(0.0, rand() % 360, 0.0);
}
