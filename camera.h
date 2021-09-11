#ifndef CAMERA_H
#define CAMERA_H

#include "glfuncs.h"
#include "mathhelper.h"

class Camera {
private:
    Vector3 direction;
    Vector3 up;
    Vector3 right;

    Vector3 lastPosition;
    glm::quat lastOrient;

    Matrix viewMatrix;

public:
    Vector3 position;
    glm::quat orientation;

    Camera(Vector3 _position = Vector3(0.0f, 0.0f, 0.0f), glm::quat _orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));

    Matrix LookAt();
    Vector3 Direction();
    Vector3 Up();
    Vector3 Right();
    void Update(float deltaTime);
};

#endif