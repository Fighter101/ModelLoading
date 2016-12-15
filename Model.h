//
// Created by madara on 03/12/16.
//

#ifndef MODELLOADING_MODEL_H
#define MODELLOADING_MODEL_H

#include "Includes.h"
#include "Mesh.h"
#include "Shader.h"

class Model {
public:
    friend class Physics;
    /*  Functions   */
    Model(GLchar* path);
    void Draw(Shader shader);
    vector<Mesh> meshes;
private:
    /*  Model Data  */

    string directory;
    vector<Texture> textures_loaded;
    /*  Functions   */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, Type textureType);
    GLuint TextureFromFile(string name, string directory);

};


#endif //MODELLOADING_MODEL_H
