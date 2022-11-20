#define GL_SILENCE_DEPRECATION

#include "material.hpp"

vector<Material> Material::materials;

Material::Material(string n)
{
    name = n;
    
    specular_exponent = 250.0;
    optic_density = 1.45;
    transparence = 1.0;
    
    ambient_color = Vector3D(1.0, 1.0, 1.0);
    diffuse_color = Vector3D(1.0, 1.0, 1.0);
    specular_color = Vector3D(1.0, 1.5, 1.0);
    emissive_color = Vector3D(0.0, 0.0, 0.0);
    
    light_parameters = 2;
    
    texture_id = 0;
    texture_scale = Vector3D(1.0, 1.0, 1.0);
}

void Material::loadAll(const string name)
{
    ifstream mtl("/Users/user/Desktop/scary_project/scary_game/Models/" + name);
    
    if (!mtl.is_open())
    {
        throw "ERROR::load::Could not open material file.";
    }
    stringstream ss;
    string line = "", prefix = "", text = "";
    double a, b, c;
    int k;
    
    while (getline(mtl, line))
    {
        ss.clear(); ss.str(line); ss >> prefix;
        
        if (prefix == "newmtl")
        {
            ss >> text;
            
            if (brandNew(text))
            {
                Material material(text);
                
                while (prefix != "map_Kd")
                {
                    getline(mtl, line);
                    ss.clear(); ss.str(line); ss >> prefix;
                    
                    if (prefix == "Ns")
                    {
                        ss >> a;
                        material.specular_exponent = a;
                    }
                    else if (prefix == "Ka")
                    {
                        ss >> a >> b >> c;
                        material.ambient_color = Vector3D(a, b, c);
                    }
                    else if (prefix == "Kd")
                    {
                        ss >> a >> b >> c;
                        material.diffuse_color = Vector3D(a, b, c);
                    }
                    else if (prefix == "Ks")
                    {
                        ss >> a >> b >> c;
                        material.specular_color = Vector3D(a, b, c);
                    }
                    else if (prefix == "Ke")
                    {
                        ss >> a >> b >> c;
                        material.emissive_color = Vector3D(a, b, c);
                    }
                    else if (prefix == "Ni")
                    {
                        ss >> a;
                        material.optic_density = a;
                    }
                    else if (prefix == "d")
                    {
                        ss >> a;
                        material.transparence = a;
                    }
                    else if (prefix == "illum")
                    {
                        ss >> k;
                        material.light_parameters = k;
                    }
                    else if (prefix == "map_Kd")
                    {
                        ss >> text;
                        if (text == "-s" )
                        {
                            ss >> a >> b >> c;
                            material.texture_scale = Vector3D(a, b, c);
                            ss >> text;
                        }
                        for (int i = 0; i < Texture::textures.size(); i++)
                        {
                            if ("/Users/user/Desktop/scary_project/scary_game/Textures/" + Texture::textures[i].name == text)
                            {
                                material.texture_id = i;
                            }
                        }
                    }
                }
                materials.push_back(material);
            }
        }
    }
}

bool Material::brandNew(const string name)
{
    for (int i = 0; i < materials.size(); i++)
    {
        if (materials[i].name == name)
        {
            return false;
        }
    }
    return true;
}

int Material::find(const string material_name)
{
    for (int i = 0; i < materials.size(); i++)
    {
        if (materials[i].name == material_name)
        {
            return i;
        }
    }
    throw "ERROR::findMaterial::Could not find material";
}

void Material::bind()
{
    Texture::textures[texture_id].bind();
    
    GLfloat ambient[] = {(GLfloat)ambient_color.x, (GLfloat)ambient_color.y, (GLfloat)ambient_color.z};
    GLfloat diffuse[] = {(GLfloat)diffuse_color.x, (GLfloat)diffuse_color.y, (GLfloat)diffuse_color.z};
    GLfloat specular[] = {(GLfloat)specular_color.x, (GLfloat)specular_color.y, (GLfloat)specular_color.z};
    GLfloat emissive[] = {(GLfloat)emissive_color.x, (GLfloat)emissive_color.y, (GLfloat)emissive_color.z};
    
//    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//    glMaterialfv(GL_FRONT, GL_EMISSION, emissive);
}
