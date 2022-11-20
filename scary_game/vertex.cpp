#define GL_SILENCE_DEPRECATION

#include "vertex.hpp"

void Vertex::draw() const
{
    glNormal3f(normal.x, normal.y, normal.z);
    glTexCoord2f(pixel.x * Material::materials[material_id].texture_scale.x, pixel.y * Material::materials[material_id].texture_scale.y);
    glVertex3f(position.x, position.y, position.z);
}
