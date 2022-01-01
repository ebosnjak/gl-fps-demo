#include "animation.h"

Animation::Animation() {
    startPos = glm::vec3(0.0f);
    endPos = glm::vec3(0.0f);
    position = startPos;

    startQuat = glm::quat(glm::vec3(0.0f));
    endQuat = glm::quat(glm::vec3(0.0f));
    quat = glm::quat(glm::vec3(0.0f));

    duration = 0.0f;
    timer = 0.0f;   

    finished = false;
    paused = false;
    started = false;
}

Animation::Animation(float dur, glm::vec3 startp, glm::vec3 endp, glm::quat startq, glm::quat endq) {
    startPos = startp;
    endPos = endp;
    position = startPos;

    startQuat = startq;
    endQuat = endq;
    quat = startQuat;

    duration = dur;
    timer = 0.0f;

    finished = false;
    paused = false;
    started = true;
}

void Animation::Update(float deltaTime) {
    if (paused || finished) {
        return;
    }

    timer += deltaTime;
    if (timer > duration) {
        timer = 0.0f;
        finished = true;
        position = endPos;
        quat = endQuat;
        return;
    }

    position = glm::mix(startPos, endPos, timer / duration);
    quat = glm::mix(startQuat, endQuat, timer / duration);
}

void Animation::Restart() {
    finished = false;
    paused = false;
    started = true;
    timer = 0.0f;

    position = startPos;
    quat = startQuat;
}