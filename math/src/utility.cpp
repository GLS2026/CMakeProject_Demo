#include <utility.hpp>
#include <iostream>

static const ODEFunction* ode_ptr = nullptr;

double State[2];
double State_curr[2];

// Euler Method
double eular(
    double t,
    double dt)
{
    double k1;

    k1 = ode_ptr->derivative(t, State_curr[0]);

    State_curr[0] += k1 * dt;
    State[0] = State_curr[0];
    
    return State[0];
}


// Runge-Kutta 4th Order Method
double rk4_step(
    double t,
    double dt)
{
    double k1, k2, k3, k4;

    k1 = ode_ptr->derivative(t, State_curr[1]);

    k2 = ode_ptr->derivative(
        t + dt / 2,
        State_curr[1] + k1 * dt / 2
    );

    k3 = ode_ptr->derivative(
        t + dt / 2,
        State_curr[1] + k2 * dt / 2
    );

    k4 = ode_ptr->derivative(
        t + dt,
        State_curr[1] + k3 * dt
    );

    State_curr[1] += (k1 + 2.0 * k2 + 2.0 * k3 + k4) * dt / 6.0;

    State[1] = State_curr[1];

    return State[1];
}

void ODEInit(const ODEFunction& ode)
{
    ode_ptr = &ode;

    // Get initial conditions from ODEFunction
    double y0 = ode.initial_y();

    // Initialize Euler state
    State_curr[0] = y0;
    State[0] = State_curr[0];

    // Initialize RK4 state
    State_curr[1] = y0;
    State[1] = State_curr[1];

    std::cout << "--- ODE Numerical Integration ---"
              << std::endl;

    std::cout << "Initial value: " << y0
              << std::endl;
}

double ODE_Eular()
{
    return State[0];
}

double ODE_RK4()
{
    return State[1];
}