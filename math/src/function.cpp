#include <ODEFunction.hpp>
#include <cmath>

double function(double x) {
    return pow(x + 1, 2) - 1.5 * exp(x);
}