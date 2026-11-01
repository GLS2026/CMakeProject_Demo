#include "../inc/mysqrt.hpp"
#include <cmath>
#include <iostream>

double function(double x) {
    return pow(x + 1, 2) - 1.5 * exp(x);
}