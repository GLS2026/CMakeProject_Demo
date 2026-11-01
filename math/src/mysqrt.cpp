#include <mysqrt.hpp>
#include <cmath>
#include <iostream>

// dy/dt = 1 / (2*y)
double ODE1::derivative(double t, double y) const
{
    return 1.0 / (2.0 * y);
}

// y(x) = sqrt(x)
double ODE1::exact_solution(double x) const
{
    return std::sqrt(x);
}

double ODE1::initial_x() const
{
    return 0.1;
}

double ODE1::initial_y() const
{
    return exact_solution(initial_x());
}