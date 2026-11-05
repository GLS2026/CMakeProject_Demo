#ifndef ODE_FUNCTION_H
#define ODE_FUNCTION_H

#include <vector>

// State Vector
using StateVector = std::vector<double>;

// Parent Class
class ODEFunction {
public:
    virtual ~ODEFunction() = default;
    virtual StateVector derivative(
        double t,
        const StateVector& state
    ) const = 0;

    virtual StateVector initial_state() const = 0;
};

// Child Class
class ODE1 : public ODEFunction {
public:
    StateVector derivative(
        double t,
        const StateVector& state
    ) const override;

    StateVector initial_state() const override;

    double exact_solution(double t) const;
};

// Second-order ODE
class ODE2 : public ODEFunction {
};

// Mass-Damper-Spring System
class MassDamperSpring : public ODE2 {
private:
    double m;   // Mass
    double c;   // Damping coefficient
    double k;   // Spring stiffness

    double x0;  // Initial position
    double v0;  // Initial velocity

public:
    MassDamperSpring(
        double mass = 1.0,
        double damping = 0.5,
        double stiffness = 4.0,
        double initial_position = 1.0,
        double initial_velocity = 0.0
    );

    StateVector derivative(
        double t,
        const StateVector& state
    ) const override;

    StateVector initial_state() const override;

    StateVector exact_solution(double t) const;
};
#endif
