#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include "Linalg.hpp"
#include "Particle.hpp"
class Solver {
    public:
        explicit Solver(const int num_particles);
        std::vector<Particle>* GetParticles() { return &fParticles; };
        void Start(bool doRandomPos);
        void InitSPH();
        void Update();
        float GetParticleSize() { return fParticleSize; }
        float GetParticleSpacing() { return fParticleSpacing; }
        void SetParticleSize(const float size);
        void SetParticleSpacing(const float spacing) { fParticleSpacing = spacing; }
    private:
        int fNParticles;
        std::vector<Particle> fParticles;
        float fParticleSize;
        float fParticleSpacing;

        Vector2 fBoundsSize;
        Vector2 fHalfBoundsSize;

        void ResolveCollisions(int i);
        void Integrate();
        void ComputeDensityPressure();
        void ComputeForces();


};

#endif