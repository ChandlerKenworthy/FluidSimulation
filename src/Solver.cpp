#include "Solver.hpp"

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
}