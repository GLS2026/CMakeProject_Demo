#include <ODEFunction.hpp>
#include <cmath>
#include <stdexcept>

// dy/dt = y - t^2 + 1
StateVector ODE1::derivative(double t, const StateVector& state) const
{
    return {state[0] - t * t + 1};
}


// y(t) = (t + 1)^2 - 1.5 * exp(t)
double ODE1::exact_solution(double x) const
{
    return pow(x + 1, 2) - 1.5 * exp(x);
}

StateVector ODE1::initial_state() const
{
    return {exact_solution(0.0)};
}

// ==========================================
// Mass-Damper-Spring
// m*x'' + c*x' + k*x = 0
// ==========================================

MassDamperSpring::MassDamperSpring(
    double mass,
    double damping,
    double stiffness,
    double initial_position,
    double initial_velocity
)
    : m(mass),
      c(damping),
      k(stiffness),
      x0(initial_position),
      v0(initial_velocity)
{
    if (m <= 0.0) {
        throw std::invalid_argument("Mass must be positive!");
    }
}

StateVector MassDamperSpring::derivative(
    double t,
    const StateVector& state
) const
{
    if (state.size() != 2) {
        throw std::invalid_argument(
            "MassDamperSpring requires 2 state variables!"
        );
    }

    double x = state[0];
    double v = state[1];

    double acceleration = (-c * v - k * x) / m;

    return {v, acceleration};
}

// Analytical solution
StateVector MassDamperSpring::exact_solution(double t) const
{
    double omega_n = std::sqrt(k / m);
    double zeta = c / (2.0 * std::sqrt(m * k));

    // Underdamped system only
    if (zeta >= 1.0) {
        throw std::invalid_argument(
            "Exact solution currently supports underdamped systems only!"
        );
    }

    double omega_d = omega_n * std::sqrt(1.0 - zeta * zeta);

    // Coefficients from initial conditions
    double A = x0;
    double B = (v0 + zeta * omega_n * x0) / omega_d;

    double decay = std::exp(-zeta * omega_n * t);

    // Position
    double position = decay * (
        A * std::cos(omega_d * t)
        + B * std::sin(omega_d * t)
    );

    // Velocity
    double velocity = decay * (
        -zeta * omega_n * (
            A * std::cos(omega_d * t)
            + B * std::sin(omega_d * t)
        )
        - A * omega_d * std::sin(omega_d * t)
        + B * omega_d * std::cos(omega_d * t)
    );

    return {position, velocity};
}


StateVector MassDamperSpring::initial_state() const
{
    return {x0, v0};
}