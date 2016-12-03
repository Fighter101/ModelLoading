//
// Created by madara on 02/12/16.
//

#include "TextureLoader.h"
GLint TextureLoader::ID = 0;
TextureLoader::TextureLoader(const string &texturePath) {
    GLint textureWidth,textureHeight;
    unsigned char *texture = SOIL_load_image(texturePath.c_str(),&textureWidth,&textureHeight,0,SOIL_LOAD_RGB);
    if(texture==NULL)
        cout<<"Can't load texture"<<endl;
    textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,textureWidth,textureHeight,0,GL_RGB,GL_UNSIGNED_BYTE,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(texture);
    glBindTexture(GL_TEXTURE_2D, 0);
    textureIndex=ID++;

}

void TextureLoader::use(GLint location) {
    if(location == -1)
        cout<<"can't find the uniform variabale, check your spelling"<<endl;
    glActiveTexture(GL_TEXTURE0 + textureIndex);
    glBindTexture(GL_TEXTURE_2D , textureID);
    glUniform1i(location , textureIndex);

}

GLuint TextureLoader::getID() {
    return textureID;
}
