#include <gtest/gtest.h>
#include <ODEFunction.hpp>
#include <utility.hpp>
#include <cmath>

TEST(MathTest, Real) {
    ODE1 ode;
    ODEInit(ode);
    const double expected_values[] = {
        -0.5, -0.447756, -0.392104, -0.334788, -0.277737, -0.223082, -0.173178, -0.130629, -0.0983114, -0.0794047,
        -0.0774227, -0.096249, -0.140175, -0.213945, -0.3228, -0.472534, -0.669549, -0.920921, -1.23447, -1.61884,
        -2.08358, -2.63925, -3.29752, -4.07127, -4.97476, -6.02374, -7.23561, -8.6296, -10.227, -12.0512,
        -14.1283, -16.4869, -19.1588, -22.179, -25.5862, -29.4232, -33.7374, -38.581, -44.0118, -50.0937,
        -56.8972, -64.5004, -72.9895, -82.4597, -93.0163, -104.776, -117.866, -132.431, -148.626, -166.625,
        -186.62, -208.823, -233.468, -260.815, -291.15, -324.788, -362.08, -403.411, -449.209, -499.946,
        -556.143, -618.377, -687.284
    };

    for (int i = 0; i < sizeof(expected_values) / sizeof(expected_values[0]); i++) {
        double x = i * 0.1;
        EXPECT_NEAR(ode.exact_solution(x), expected_values[i], 1e-3);
    }
}

TEST(MathTest, Eular) {
    ODE1 ode;
    ODEInit(ode);
    double t = 0;
    StateVector yEular = ODE_Eular();
    const double expected_values[] = {
        -0.5, -0.447756, -0.392104, -0.334788, -0.277737, -0.223082, -0.173178, -0.130629, -0.0983114, -0.0794047,
        -0.0774227, -0.096249, -0.140175, -0.213945, -0.3228, -0.472534, -0.669549, -0.920921, -1.23447, -1.61884,
        -2.08358, -2.63925, -3.29752, -4.07127, -4.97476, -6.02374, -7.23561, -8.6296, -10.227, -12.0512,
        -14.1283, -16.4869, -19.1588, -22.179, -25.5862, -29.4232, -33.7374, -38.581, -44.0118, -50.0937,
        -56.8972, -64.5004, -72.9895, -82.4597, -93.0163, -104.776, -117.866, -132.431, -148.626, -166.625,
        -186.62, -208.823, -233.468, -260.815, -291.15, -324.788, -362.08, -403.411, -449.209, -499.946,
        -556.143, -618.377, -687.284
    };

    for (int i = 1; i < (sizeof(expected_values) / sizeof(expected_values[0]))-1; i++) {
        yEular = eular(t, 0.1);
        t += 0.1;
        EXPECT_NEAR(yEular[0], expected_values[i], 1e-2);
    }
}

TEST(MathTest, RangeKutta4) {
    ODE1 ode;
    ODEInit(ode);
    double t = 0.0;
    StateVector yRK4 = ODE_RK4();
    const double expected_values[] = {
        -0.5, -0.447756, -0.392104, -0.334788, -0.277737, -0.223082, -0.173178, -0.130629, -0.0983114, -0.0794047,
        -0.0774227, -0.096249, -0.140175, -0.213945, -0.3228, -0.472534, -0.669549, -0.920921, -1.23447, -1.61884,
        -2.08358, -2.63925, -3.29752, -4.07127, -4.97476, -6.02374, -7.23561, -8.6296, -10.227, -12.0512,
        -14.1283, -16.4869, -19.1588, -22.179, -25.5862, -29.4232, -33.7374, -38.581, -44.0118, -50.0937,
        -56.8972, -64.5004, -72.9895, -82.4597, -93.0163, -104.776, -117.866, -132.431, -148.626, -166.625,
        -186.62, -208.823, -233.468, -260.815, -291.15, -324.788, -362.08, -403.411, -449.209, -499.946,
        -556.143, -618.377, -687.284
    };

    for (int i = 1; i < (sizeof(expected_values) / sizeof(expected_values[0]))-1; i++) {
        yRK4 = rk4_step(t, 0.1);
        t += 0.1;
        EXPECT_NEAR(yRK4[0], expected_values[i], 1e-2);
    }
}


// ==========================================
// ODE2: Mass-Damper-Spring
// ==========================================

// Test analytical solution
TEST(MathTest, ODE2_Real) {
    MassDamperSpring ode(
        1.0, 0.5, 4.0, 1.0, 0.0
    );

    // Initial conditions
    StateVector initial = ode.exact_solution(0.0);

    ASSERT_EQ(initial.size(), 2);
    EXPECT_NEAR(initial[0], 1.0, 1e-6);
    EXPECT_NEAR(initial[1], 0.0, 1e-6);

    // Expected analytical values
    const double expected_values[][2] = {
        {0.9803944709, -0.3875688119},
        {0.5757089567, -1.4893472373},
        {-0.2230979955, -1.4375916891},
        {-0.4668947505, 0.8997813813}
    };

    const double test_times[] = {
        0.1, 0.5, 1.0, 2.0
    };

    for (int i = 0; i < 4; i++) {
        StateVector result =
            ode.exact_solution(test_times[i]);

        EXPECT_NEAR(result[0], expected_values[i][0], 1e-6);
        EXPECT_NEAR(result[1], expected_values[i][1], 1e-6);
    }
}


// Test Euler method
TEST(MathTest, ODE2_Eular) {
    MassDamperSpring ode(
        1.0, 0.5, 4.0, 1.0, 0.0
    );

    ODEInit(ode);

    double t = 0.0;
    double h = 0.01;

    StateVector yEular = ODE_Eular();

    for (int i = 0; i < 200; i++) {

        yEular = eular(t, h);
        t += h;

        StateVector yReal = ode.exact_solution(t);

        EXPECT_NEAR(yEular[0], yReal[0], 1e-2);
        EXPECT_NEAR(yEular[1], yReal[1], 1e-2);
    }
}


// Test Runge-Kutta 4th Order method
TEST(MathTest, ODE2_RK4) {
    MassDamperSpring ode(
        1.0, 0.5, 4.0, 1.0, 0.0
    );

    ODEInit(ode);

    double t = 0.0;
    double h = 0.01;

    StateVector yRK4 = ODE_RK4();

    for (int i = 0; i < 200; i++) {

        yRK4 = rk4_step(t, h);
        t += h;

        StateVector yReal = ode.exact_solution(t);

        EXPECT_NEAR(yRK4[0], yReal[0], 1e-2);
        EXPECT_NEAR(yRK4[1], yReal[1], 1e-2);
    }
}