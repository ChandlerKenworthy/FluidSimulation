#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include "Particle.hpp"
class Solver {
    public:
        explicit Solver(const int num_particles);
        std::vector<Particle>* GetParticles() { return &fParticles; };
        void Start();
        void InitSPH();
        void Integrate();
        void ComputeDensityPressure();
        void ComputeForces();
        void Update();
        float GetParticleSize() { return fParticleSize; }
        float GetParticleSpacing() { return fParticleSpacing; }
        void SetParticleSize(const float size) { fParticleSize = size; }
        void SetParticleSpacing(const float spacing) { fParticleSpacing = spacing; }
    private:
        int fNParticles;
        std::vector<Particle> fParticles;
        float fParticleSize;
        float fParticleSpacing;


};

#endif