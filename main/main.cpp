#include <iostream>
#include <utility.hpp>
#include <ODEFunction.hpp>
#include <fstream>
#include <cmath>

#define PI 3.14159265

const char* FILENAME = "Numerical_data.csv";

void process_csv()
{
    ODE1 ode;

    ODEInit(ode);
    
    std::ofstream csv_file(FILENAME);

    if (!csv_file.is_open()) {
        std::cerr << "Cannot open CSV file!" << std::endl;
        return;
    }

    csv_file << "Real,Eular,RK4\n";

    double t = 0;
    double h = 0.1;

    // Initial value
    StateVector yEular = ODE_Eular();
    StateVector yRK4 = ODE_RK4();

    while (t < 2 * PI)
    {
        // Analytical solution
        double yReal = ode.exact_solution(t);

        std::cout << yReal << "," << yEular[0] << "," << yRK4[0] << std::endl;

        // Save numerical results
        csv_file << yReal << "," << yEular[0] << "," << yRK4[0] << "\n";

        // Numerical integration
        yEular = eular(t, h);
        yRK4 = rk4_step(t, h);

        t += h;
    }

    csv_file.close();
}

int main()
{
    std::cout << "Main application started." << std::endl;

    process_csv();

    std::cout << "Main application finished." << std::endl;

    return 0;
}