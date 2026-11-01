#ifndef UTILITY_H
#define UTILITY_H

#include "ODEFunction.hpp"

double eular(
    const ODEFunction& ode,
    double t,
    double y,
    double dt
);

double rk4_step(
    const ODEFunction& ode,
    double t,
    double y,
    double dt
);

#endif