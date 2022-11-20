#define GL_SILENCE_DEPRECATION

#include "model.hpp"
#include "game.hpp"

#include "stb_image.hpp"

vector<Model> Model::models;

//============================================ CREATION ================================================//

Model::Model(const string model_name)
{
    name = model_name;
    
    //Vertex portions
    vector<Vector3D> positions;
    vector<Vector3D> pixels;
    vector<Vector3D> normals;

    //Face vectors
    vector<int> position_indicies;
    vector<int> pixel_indicies;
    vector<int> normal_indicies;
    vector<int> material_indices;

    //stockage temporaire des données du fichier
    stringstream ss;
    string line = "", prefix = "", name = "";
    double a, b, c;
    int index = 0, material = 0;
    
    ifstream obj("/Users/user/Desktop/scary_project/scary_game/Models/" + model_name + ".obj");

    //erreur de chargement
    if (!obj.is_open())
    {
        throw "ERROR::load::Could not open object file.";
    }
    
    while (getline(obj, line))
    {
        ss.clear(); ss.str(line); ss >> prefix;
        
        if (prefix == "mtllib") //importation de la bibliothèque de materiaux
        {
            ss >> name;
            Material::loadAll(name);
        }
        if (prefix == "usemtl") //materiau
        {
            ss >> name;
            material = Material::find(name);
        }
        else if (prefix == "v") //position
        {
            ss >> a >> b >> c;
            positions.push_back(Vector3D(a, b, c));
        }
        else if (prefix == "vt") //coordonées de texture
        {
            ss >> a >> b;
            pixels.push_back(Vector3D(a, b, 0.0));
        }
        else if (prefix == "vn") //normales
        {
            ss >> a >> b >> c;
            normals.push_back(Vector3D(a, b, c));
        }
        else if (prefix == "f")
        {
            material_indices.push_back(material); material_indices.push_back(material); material_indices.push_back(material);

            int counter = 0;
            while (ss >> index)
            {
                switch (counter % 3)
                {
                    case 0 :
                        position_indicies.push_back(index);
                        break;
                    case 1 :
                        pixel_indicies.push_back(index);
                        break;
                    case 2 :
                        normal_indicies.push_back(index);
                        break;
                }
                if (ss.peek() == '/')
                {
                    ++counter;
                    ss.ignore(1, '/');
                }
                else if (ss.peek() == ' ')
                {
                    ++counter;
                    ss.ignore(1, ' ');
                }
            }
        }
    }

    vertices.resize(position_indicies.size());

    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].material_id = material_indices[i];
        vertices[i].position = positions[position_indicies[i] - 1];
        vertices[i].pixel = pixels[pixel_indicies[i] - 1];
        vertices[i].normal = normals[normal_indicies[i] - 1];
    }
    
    //DEBUG
    std::cout << "Model " << model_name << " loaded." << endl;
}

void Model::loadAll()
{
    ifstream file;
    string model_name;
    
    file.open("/Users/user/Desktop/scary_project/scary_game/Models/model_list.txt");
    
    while (!file.eof())
    {
        file >> model_name;
        Model m(model_name);
        models.push_back(m);
    }
    file.close();
}

void Model::draw() const
{
    for (int i = 0; i < vertices.size(); i+=3)
    {
        if (i == 0 || vertices[i].material_id != vertices[i - 1].material_id)
        {
            Material::materials[vertices[i].material_id].bind();
        }
        
        glBegin(GL_TRIANGLES);
        
        vertices[i].draw();
        vertices[i+1].draw();
        vertices[i+2].draw();

        glEnd();
    }
    
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
