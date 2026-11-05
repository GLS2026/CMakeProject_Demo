#ifndef UTILITY_H
#define UTILITY_H

#include "ODEFunction.hpp"

void ODEInit(const ODEFunction& ode);

double eular(
    double t,
    double dt
);

double rk4_step(
    double t,
    double dt
);

double ODE_Eular();
double ODE_RK4();
#endif