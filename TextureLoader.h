//
// Created by madara on 02/12/16.
//

#ifndef LIGHTING_TEXTURE_H
#define LIGHTING_TEXTURE_H

#include "Includes.h"
class TextureLoader {
private:
    GLint  textureIndex;
    GLuint textureID;
public:
    TextureLoader(const string &texturePath);
    void use(GLint location);
    GLuint getID();
    static GLint ID;

};


#endif //LIGHTING_TEXTURE_H
