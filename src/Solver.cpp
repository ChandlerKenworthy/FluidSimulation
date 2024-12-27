#include "Solver.hpp"
#include "Constants.hpp"

Solver::Solver(const int num_particles) : fNParticles(num_particles), fParticles(), fParticleSize(0.04f), fParticleSpacing(0.02f) { }

void Solver::Start() {
    // TODO: Add an option to this to instead place the particles randomly
    // Create the particles and place them in a grid formation
    int particlesPerRow = (int)sqrt(fNParticles);
    int particlesPerCol = (fNParticles - 1) / particlesPerRow + 1;
    float spacing = fParticleSize * 2 + fParticleSpacing;

    for(int i = 0; i < fNParticles; ++i) {
        float x = (i % particlesPerRow - particlesPerRow / 2.0 + 0.5) * spacing;
        float y = (i / particlesPerRow - particlesPerCol / 2.0 + 0.5) * spacing;
        fParticles.push_back(Particle(
            Vector2(x, y),
            Vector2(0.0f, 0.0f)
        ));
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

    Vector2 boundsSize(2., 2.); // +/- 1 in each direction
    Vector2 halfBoundsSize = boundsSize / 2 - VEC_ONES * fParticleSize;

    // Out of bounds in x
    if(fabs(pa->p.x) > halfBoundsSize.x) {
        pa->p = halfBoundsSize.x * Sign(pa->p.x);
        pa->v *= -1.0;
    }

    if(fabs(pa->p.y) > halfBoundsSize.y) {
        pa->p.y = halfBoundsSize.y * Sign(pa->p.y);
        pa->v *= -1.0;
    }

}