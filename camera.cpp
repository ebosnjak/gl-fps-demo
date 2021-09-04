#include "camera.h"

Camera::Camera(Vector3 _position, float _yaw, float _pitch) {
    position = _position;
    yaw = _yaw;
    pitch = _pitch;

    ComputeVectors();
}

Matrix Camera::LookAt() {
    ComputeVectors();
    return Matrix::CreateLookAt(position, position + direction, up);
}

Vector3 Camera::Direction() {
    ComputeVectors();
    return direction;
}

Vector3 Camera::Up() {
    ComputeVectors();
    return up;
}

Vector3 Camera::Right() {
    ComputeVectors();
    return right;
}

void Camera::ComputeVectors() {
    if (lastYaw != yaw || lastPitch != pitch || lastPosition != position) {
        if (pitch > 87.0f) pitch = 87.0f;
        if (pitch < -87.0f) pitch = -87.0f;

        direction = Vector3(Math::Cos(yaw) * Math::Cos(pitch), Math::Sin(pitch), -Math::Sin(yaw) * Math::Cos(pitch));
        right = Vector3::Cross(direction, Vector3(0.0f, 1.0f, 0.0f)).Normalize();
        up = Vector3::Cross(right, direction).Normalize();

        lastPosition = position;
        lastYaw = yaw;
        lastPitch = pitch;
    }
}