#include <utility.hpp>
#include <iostream>

static const ODEFunction* ode_ptr = nullptr;

static StateVector State_Euler;
static StateVector State_RK4;

static StateVector add_scaled(
    const StateVector& state,
    const StateVector& derivative,
    double scale)
{
    if (state.size() != derivative.size()) {
        throw std::runtime_error("State dimension mismatch!");
    }

    StateVector result(state.size());

    for (std::size_t i = 0; i < state.size(); ++i) {
        result[i] = state[i] + derivative[i] * scale;
    }

    return result;
}

// Euler Method
StateVector eular(
    double t,
    double dt)
{
    if (ode_ptr == nullptr) {
        throw std::runtime_error("ODE is not initialized!");
    }

    StateVector k1 = ode_ptr->derivative(t, State_Euler);

    State_Euler = add_scaled(State_Euler, k1, dt);

    return State_Euler;
}


// Runge-Kutta 4th Order Method
StateVector rk4_step(
    double t,
    double dt)
{
    if (ode_ptr == nullptr) {
        throw std::runtime_error("ODE is not initialized!");
    }

    StateVector k1, k2, k3, k4;
    StateVector temp;

    k1 = ode_ptr->derivative(t, State_RK4);

    temp = add_scaled(State_RK4, k1, dt / 2.0);
    k2 = ode_ptr->derivative(t + dt / 2.0, temp);

    temp = add_scaled(State_RK4, k2, dt / 2.0);
    k3 = ode_ptr->derivative(t + dt / 2.0, temp);

    temp = add_scaled(State_RK4, k3, dt);
    k4 = ode_ptr->derivative(t + dt, temp);

    if (k1.size() != k2.size() ||
        k1.size() != k3.size() ||
        k1.size() != k4.size()) {
        throw std::runtime_error("RK4 derivative dimension mismatch!");
    }

    for (std::size_t i = 0; i < State_RK4.size(); ++i) {
        State_RK4[i] +=
            (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i])
            * dt / 6.0;
    }

    return State_RK4;
}

void ODEInit(const ODEFunction& ode)
{
    ode_ptr = &ode;

    // Get initial conditions from ODEFunction
    StateVector initial = ode.initial_state();

    if (initial.empty()) {
        throw std::runtime_error("Initial state is empty!");
    }

    // Initialize Euler state
    State_Euler = initial;

    // Initialize RK4 state
    State_RK4 = initial;

    std::cout << "--- ODE Numerical Integration ---"
              << std::endl;

        std::cout << "Initial state: ";

    for (double value : initial) {
        std::cout << value << " ";
    }

    std::cout << std::endl;
}

StateVector ODE_Eular()
{
    return State_Euler;
}

StateVector ODE_RK4()
{
    return State_RK4;
}