#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Linalg.hpp"

struct Particle {
    Vector2 p; // position
    Vector2 v; // velocity
    Particle(Vector2 pos, Vector2 vel, float r = 1.0f) : p(pos), v(vel) { }
};

#endif