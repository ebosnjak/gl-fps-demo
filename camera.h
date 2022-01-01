#ifndef CAMERA_H
#define CAMERA_H

#include "glfuncs.h"
#include "mathhelper.h"

class Camera {
private:
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 right;

    glm::vec3 lastPosition;
    glm::quat lastOrient;

    glm::mat4 viewMatrix;

public:
    glm::vec3 position;
    glm::quat orientation;

    Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat _orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));

    glm::mat4 LookAt();
    glm::vec3 Direction();
    glm::vec3 Up();
    glm::vec3 Right();
    void Update(float deltaTime);
};

#endif