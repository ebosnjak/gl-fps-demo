#ifndef ANIMATION_H
#define ANIMATION_H

#include "mathhelper.h"

struct Animation {
    glm::vec3 startPos, endPos, position;
    glm::quat startQuat, endQuat, quat;
    float duration, timer;
    bool started, finished, paused;

    Animation();
    Animation(float dur, glm::vec3 startp, glm::vec3 endp, 
              glm::quat startq = glm::quat(glm::vec3(0.0f)), glm::quat endq = glm::quat(glm::vec3(0.0f)));

    void Restart();
    void Update(float deltaTime);
};

#endif