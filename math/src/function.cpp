#include <ODEFunction.hpp>
#include <cmath>

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