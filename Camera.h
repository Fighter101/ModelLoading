//
// Created by madara on 01/12/16.
//

#ifndef LIGHTING_CAMERA_H
#define LIGHTING_CAMERA_H
#include "Includes.h"
enum Direction
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    GLfloat mouseYaw=-90.0f , mousePitch=0.0f;
    GLfloat fov=45.0f;
    glm::vec3 cameraPos  , cameraFront , cameraUp;
    glm::mat4 view;
    glm::mat4 transofrmation;
    glm::vec3 carPosition;
    glm::vec3 carRotation;
    btQuaternion carQuaternion;
    bool first= true;
    glm::vec3 eye;
public:
    Camera(glm::vec3 cameraPosition);
    glm::mat4 getViewMatrix();
    void processKeyBoard(Direction direction, GLfloat deltaTime);
    void processMouseMovement(GLfloat xOffset , GLfloat yOffset);
    void processMouseScroll(GLfloat yOffset);
    GLfloat Zoom;
};


#endif //LIGHTING_CAMERA_H
