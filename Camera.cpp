//
// Created by madara on 01/12/16.
//

#include "Camera.h"
void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset) {
    GLfloat sensitivity = 0.05f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;
    mouseYaw = mouseYaw+ xOffset;
    mousePitch += yOffset;
    if(mousePitch > 89.0f)
        mousePitch =  89.0f;
    if(mousePitch < (-89.0f))
        mousePitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(mousePitch)) * cos(glm::radians(mouseYaw));
    front.y = sin(glm::radians(mousePitch));
    front.z = cos(glm::radians(mousePitch)) * sin(glm::radians(mouseYaw));
    cameraFront = glm::normalize(front);
    eye = glm::vec3(5,5,5);

}

void Camera::processKeyBoard(Direction direction, GLfloat deltaTime) {

    GLfloat cameraSpeed = 5.0f*deltaTime;
    if(direction==FORWARD)
        cameraPos += cameraSpeed * cameraFront;
    if(direction == BACKWARD)
        cameraPos -= cameraSpeed * cameraFront;
    if(direction == LEFT)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(direction == RIGHT)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


}

void Camera::processMouseScroll(GLfloat yOffset) {
    if(fov >= 1.0f && fov <= 120.0f)
        fov -= yOffset;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 120.0f)
        fov = 120.0f;
    Zoom=fov;

}

glm::mat4 Camera::getViewMatrix() {

    return glm::lookAt(eye,carPosition, cameraUp);
}

Camera::Camera(glm::vec3 cameraPosition) {
    cameraPos   = cameraPosition;
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); //looking at -ve direction of z axis (k2nk nta elly bass)
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    Zoom=45.0f;

}
