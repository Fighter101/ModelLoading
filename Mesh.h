//
// Created by madara on 03/12/16.
//

#ifndef MODELLOADING_MESH_H
#define MODELLOADING_MESH_H
#include "Includes.h"
#include "Shader.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};
enum Type
{
    DIFFUSE,
    SPECULAR
};
struct Texture {
    GLuint id;
    Type type;
    string path;
};

class Mesh {
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    /*  Functions  */
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
    void Draw(Shader shader);
private:
    /*  Render data  */
    GLuint vertexArrayObject, vertexBufferObject, elementBufferObject;
    /*  Functions    */
    void setupMesh();
    GLuint TextureFromFile(string name,string directory);
};




#endif //MODELLOADING_MESH_H
