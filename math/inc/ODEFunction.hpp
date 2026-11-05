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
#endif
