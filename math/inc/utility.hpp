#ifndef UTILITY_H
#define UTILITY_H

#include "ODEFunction.hpp"

void ODEInit(const ODEFunction& ode);

StateVector eular(
    double t,
    double dt
);

StateVector rk4_step(
    double t,
    double dt
);

StateVector ODE_Eular();
StateVector ODE_RK4();
#endif