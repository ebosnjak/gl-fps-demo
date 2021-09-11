#include "camera.h"

Camera::Camera(Vector3 _position, glm::quat _orientation) {
    position = _position;
    orientation = _orientation;
    
    glm::quat q = orientation * glm::quat(0.0f, 0.0f, 0.0f, -1.0f) * glm::conjugate(orientation);
    direction = Vector3(q.x, q.y, q.z).Normalize();
    right = Vector3::Cross(direction, Vector3(0.0f, 1.0f, 0.0f)).Normalize();
    up = Vector3::Cross(right, direction).Normalize();
}

Matrix Camera::LookAt() {
    return viewMatrix;
}

Vector3 Camera::Direction() {
    return direction;
}

Vector3 Camera::Up() {
    return up;
}

Vector3 Camera::Right() {
    return right;
}

void Camera::Update(float deltaTime) {
    if (lastPosition != position || lastOrient != orientation) {
        glm::quat q = orientation * glm::quat(0.0f, 0.0f, 0.0f, -1.0f) * glm::conjugate(orientation);
        direction = Vector3(q.x, q.y, q.z).Normalize();
        right = Vector3::Cross(direction, Vector3(0.0f, 1.0f, 0.0f)).Normalize();
        up = Vector3::Cross(right, direction).Normalize();

        glm::mat4 rotate = glm::mat4_cast(glm::inverse(orientation));
        glm::mat4 transl = glm::translate(glm::mat4(1.0f), glm::vec3(-position.X, -position.Y, -position.Z));

        viewMatrix = Matrix(rotate * transl);

        lastPosition = position;
        lastOrient = orientation;
    }
}