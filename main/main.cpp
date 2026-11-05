#include <iostream>
#include <utility.hpp>
#include <ODEFunction.hpp>
#include <fstream>
#include <cmath>

#define PI 3.14159265

const char* FILENAME = "Numerical_data.csv";

void process_csv()
{
    // External force (N)
    const double force = 10.0;

    // Mass-Damper-Spring parameters
    MassDamperSpring ode(
        1.0,    // Mass (kg)
        0.5,    // Damping coefficient (N·s/m)
        4.0,    // Spring stiffness (N/m)
        1.0,    // Initial position (m)
        0.0,     // Initial velocity (m/s)
        [force](double t) {
        return force;
    }
    );

    ODEInit(ode);
    
    std::ofstream csv_file(FILENAME);

    if (!csv_file.is_open()) {
        std::cerr << "Cannot open CSV file!" << std::endl;
        return;
    }

    csv_file << "Time,"
             << "Position_Eular,Velocity_Eular,"
             << "Position_RK4,Velocity_RK4\n";

    double t = 0;
    double h = 0.1;

    // Initial value
    StateVector yEular = ODE_Eular();
    StateVector yRK4 = ODE_RK4();

    while (t < 30.0)
    {
        // Analytical solution
        StateVector yReal = ode.exact_solution(t, force);

        // Display results
        std::cout << t << ","
                  << yReal[0] << "," << yReal[1] << ","
                  << yEular[0] << "," << yEular[1] << ","
                  << yRK4[0] << "," << yRK4[1]
                  << std::endl;

        // Save results
        csv_file << t << ","
                 << yReal[0] << "," << yReal[1] << ","
                 << yEular[0] << "," << yEular[1] << ","
                 << yRK4[0] << "," << yRK4[1]
                 << "\n";

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