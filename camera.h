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
    float lastYaw, lastPitch;

    void ComputeVectors();

public:
    Vector3 position;

    float yaw;
    float pitch;

    Camera(Vector3 _position = Vector3(0.0f, 0.0f, 0.0f), float _yaw = 0.0f, float _pitch = 0.0f);

    Matrix LookAt();
    Vector3 Direction();
    Vector3 Up();
    Vector3 Right();
};

#endif