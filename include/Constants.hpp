#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

float Sign(float x) {
    return x < 0 ? -1.0f : 1.0f;
}

const float GRAVITY = 9.81;
const float DELTA_TIME = 1. / 60.; // 1/60th of a second
const float COLLISION_DAMPING = 0.8;

#endif