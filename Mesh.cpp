//
// Created by madara on 03/12/16.
//

#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->setupMesh();

}

void Mesh::Draw(Shader shader) {
    GLuint diffuseNr = 0;
    GLuint specularNr = 0;
    for(GLuint i = 0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
        // Retrieve texture number (the N in diffuse_textureN)
        GLuint number;
        string name;
        if(this->textures[i].type==Type::DIFFUSE) {
            name = "diffuse";
            number=diffuseNr++;
        }
        else {
            name = "specular";
            number = specularNr++;
        }
        glUniform1i(glGetUniformLocation(shader.Program, ("material." + name + "_"+to_string(number)).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
    glUniform1i(glGetUniformLocation(shader.Program,("material.numDiffuseTextures")),diffuseNr);
    glUniform1i(glGetUniformLocation(shader.Program,"material.numSpecularTextures"),specularNr);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &this->vertexArrayObject);
    glGenBuffers(1, &this->vertexBufferObject);
    glGenBuffers(1, &this->elementBufferObject);

    glBindVertexArray(this->vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)0);
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex, Normal));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

}

