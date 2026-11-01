#include <iostream>
#include <utility.hpp>
#include <mysqrt.hpp>
#include <fstream>
#include <cmath>

#define PI 3.14159265

const char* FILENAME = "Numerical_data.csv";

int main()
{
    std::cout << "Main application started." << std::endl;

    // 建立 ODE1 物件
    ODE1 ode;

    std::ofstream csv_file(FILENAME);

    if (!csv_file.is_open()) {
        std::cerr << "Cannot open CSV file!" << std::endl;
        return 1;
    }

    csv_file << "Real,Eular,RK4\n";

    double t = ode.initial_x();
    double h = 0.1;

    // Initial value
    double yEular = ode.exact_solution(t);
    double yRK4 = ode.exact_solution(t);

    while (t < 2 * PI)
    {
        // Analytical solution
        double yReal = ode.exact_solution(t);

        std::cout << yReal << "," << yEular << "," << yRK4 << std::endl;

        // Save numerical results
        csv_file << yReal << "," << yEular << "," << yRK4 << "\n";

        // Numerical integration
        yEular = eular(ode, t, yEular, h);
        yRK4 = rk4_step(ode, t, yRK4, h);

        t += h;
    }

    csv_file.close();

    std::cout << "Main application finished." << std::endl;

    return 0;
}