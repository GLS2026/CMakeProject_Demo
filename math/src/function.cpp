#include <ODEFunction.hpp>
#include <cmath>

// dy/dt = y - t^2 + 1
double ODE1::derivative(double t, double y) const
{
    return y - t * t + 1;
}

// y(t) = (t + 1)^2 - 1.5 * exp(t)
double ODE1::exact_solution(double x) const
{
    return pow(x + 1, 2) - 1.5 * exp(x);
}

double ODE1::initial_x() const
{
    return 0;
}

double ODE1::initial_y() const
{
    return exact_solution(initial_x());
}