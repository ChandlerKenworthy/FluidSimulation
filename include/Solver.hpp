#ifndef SOLVER_HPP
#define SOLVER_HPP

class Solver {
    public:
        explicit Solver();
        void InitSPH();
        void Integrate();
        void ComputeDensityPressure();
        void ComputeForces();
        void Update();
    private:

};

#endif