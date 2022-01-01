#include "camera.h"

Camera::Camera(glm::vec3 _position, glm::quat _orientation) {
    position = _position;
    orientation = _orientation;
    
    glm::quat q = orientation * glm::quat(0.0f, 0.0f, 0.0f, -1.0f) * glm::conjugate(orientation);
    direction = glm::normalize(glm::vec3(q.x, q.y, q.z));
    right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
    up = glm::cross(right, direction);
}

glm::mat4 Camera::LookAt() {
    return viewMatrix;
}

glm::vec3 Camera::Direction() {
    return direction;
}

glm::vec3 Camera::Up() {
    return up;
}

glm::vec3 Camera::Right() {
    return right;
}

void Camera::Update(float deltaTime) {
    if (lastPosition != position || lastOrient != orientation) {
        glm::quat q = orientation * glm::quat(0.0f, 0.0f, 0.0f, -1.0f) * glm::conjugate(orientation);
        direction = glm::normalize(glm::vec3(q.x, q.y, q.z));
        right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
        up = glm::cross(right, direction);

        glm::mat4 rotate = glm::mat4_cast(glm::inverse(orientation));
        glm::mat4 transl = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, -position.z));

        viewMatrix = rotate * transl;

        lastPosition = position;
        lastOrient = orientation;
    }
}