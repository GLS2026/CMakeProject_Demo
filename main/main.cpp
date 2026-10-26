#include <iostream>
#include <mysqrt.hpp>

int main() {
    double input = 25.0;
    double result = mysqrt(input);
    std::cout << "Test App: Square root of " << input << " is " << result << std::endl;
    return 0;
}