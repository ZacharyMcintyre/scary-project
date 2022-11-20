#define GL_SILENCE_DEPRECATION

#include "texture.hpp"
#include "stb_image.hpp"

vector<Texture> Texture::textures;

Texture::Texture(const string name)
{
    this->name = name;
    
    int channels;
    
    glGenTextures(1, &id);
    
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    unsigned char* image = stbi_load(("/Users/user/Desktop/scary_project/scary_game/Textures/" + name).c_str(), &width, &height, &channels, 0);
    
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else
    {
        throw "ERROR::Texture : Failed to load texture";
    }

    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    //DEBUG
    std::cout << "Texture " << name << " loaded." << endl;
}

void Texture::loadAll()
{
    glActiveTexture(GL_TEXTURE_2D);
    
    ifstream file;
    string texture_name;
    
    file.open("/Users/user/Desktop/scary_project/scary_game/Textures/texture_list.txt");
    
    while (!file.eof())
    {
        file >> texture_name;
        
        Texture t(texture_name);
        textures.push_back(t);
    }
    file.close();
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
    glEnable(GL_TEXTURE_2D);
}
