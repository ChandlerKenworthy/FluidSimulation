#include <random>
#include "Solver.hpp"
#include "Constants.hpp"

Solver::Solver(const int num_particles) : fNParticles(num_particles), fParticles(), fParticleSize(0.04f), fParticleSpacing(0.02f) {
    fBoundsSize = Vector2(2., 2.); // +/- 1 in each direction
    fHalfBoundsSize = fBoundsSize / 2 - VEC_ONES * fParticleSize;
 }

void Solver::SetParticleSize(const float size) {
    fParticleSize = size;
    fHalfBoundsSize = fBoundsSize / 2 - VEC_ONES * fParticleSize;
}

void Solver::Start(bool doRandomPos) {
    // TODO: Add an option to this to instead place the particles randomly
    // Create the particles and place them in a grid formation
    if(doRandomPos) {
        std::random_device rd;  // Seed
        std::mt19937 gen(rd()); // Mersenne Twister generator

        // Define a uniform real distribution in the range [-1, 1]
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

        for(int i = 0; i < fNParticles; ++i) {
            float x = dist(gen); // generate a random float
            float y = dist(gen); // generate another random float
            fParticles.push_back(Particle(
                Vector2(x, y),
                Vector2(0.0, 0.0)
            ));
        }

    // Generate a random float
    float randomFloat = dist(gen);
    } else {
        int particlesPerRow = (int)sqrt(fNParticles);
        int particlesPerCol = (fNParticles - 1) / particlesPerRow + 1;
        float spacing = fParticleSize * 2 + fParticleSpacing;

        for(int i = 0; i < fNParticles; ++i) {
            float x = (i % particlesPerRow - particlesPerRow / 2.0 + 0.5) * spacing;
            float y = (i / particlesPerRow - particlesPerCol / 2.0 + 0.5) * spacing;
            fParticles.push_back(Particle(
                Vector2(x, y),
                Vector2(0.0, 0.0)
            ));
        }
    }
}

void Solver::InitSPH() {}
void Solver::Integrate() {}
void Solver::ComputeDensityPressure() {}
void Solver::ComputeForces() {}


void Solver::Update() {
    // TODO: This is currently just a dummy update function

    // loop over all particles
    for(int i = 0; i < fNParticles; ++i) {
        Particle *pa = &fParticles.at(i);

        pa->v += VEC_DOWN * GRAVITY * DELTA_TIME;
        pa->p += pa->v * DELTA_TIME;

        ResolveCollisions(i);
    }
}

void Solver::ResolveCollisions(int i) {
    Particle *pa = &fParticles.at(i);
    // Out of bounds in x
    if(fabs(pa->p.x) > fHalfBoundsSize.x) {
        pa->p = fHalfBoundsSize.x * Sign(pa->p.x);
        pa->v *= -1.0;
    }

    if(fabs(pa->p.y) > fHalfBoundsSize.y) {
        pa->p.y = fHalfBoundsSize.y * Sign(pa->p.y);
        pa->v *= -1.0;
    }

}