#include <utility.hpp> 

// Euler Method
double eular(
    const ODEFunction& ode,
    double t,
    double y,
    double dt)
{
    double dy = ode.derivative(t, y);

    return y + dy * dt;
}


// Runge-Kutta 4th Order Method
double rk4_step(
    const ODEFunction& ode,
    double t,
    double y,
    double dt)
{
    double k1, k2, k3, k4;

    k1 = ode.derivative(t, y);

    k2 = ode.derivative(
        t + dt / 2,
        y + k1 * dt / 2
    );

    k3 = ode.derivative(
        t + dt / 2,
        y + k2 * dt / 2
    );

    k4 = ode.derivative(
        t + dt,
        y + k3 * dt
    );

    return y + (k1 + 2.0 * k2 + 2.0 * k3 + k4) * dt / 6.0;
}