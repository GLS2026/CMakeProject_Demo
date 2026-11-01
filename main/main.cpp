#include <iostream>
#include <ODEFunction.hpp>

int main() {
    double input = 6.2;
    double result = function(input);
    std::cout << "Test App: The output of " << input << " is " << result << std::endl;
    return 0;
}