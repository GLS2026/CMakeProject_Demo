# CMakeProject_Demo
A step by step guidance to use Cmake(Cross-platform make) to build large-scale projects 

# User Guide
Use cmake to generate makefile
```
# How to choose <makefile generator>?
# Linux gcc/gpp:Unix Makefiles, Windows minGW:MinGW Makefiles

cd wrapper
cmake -G "<makefile generator>" ..
```
Execute makefile to build source code into executables
```
cmake --build . # generate execuables in current dir
cmake --install . # After successful build, generate execuables in "install" folder from the root
```

# How to use
Execute NumericalProject under `wrapper`
```
#Linux
./main/NumericalProject
../install/bin/NumericalProject
#windows
main\NumericalProject
..\install\bin\NumericalProject
```
Execute test_math under `wrapper`
```
ctest
#linux
../install/bin/test_math
#windows
..\install\bin\test_math
```

## ODE2 Numerical Integration Results

### Mass-Damper-Spring System

The following figure compares the analytical solution (Real) with the numerical solutions obtained using the Euler method and the fourth-order Runge-Kutta method (RK4).

### Numerical Analysis

- **Analytical Solution (Real):** The theoretical solution used as the reference for numerical accuracy.
- **Euler Method:** A first-order numerical integration method. Its accumulated numerical error becomes increasingly noticeable over time.
- **Runge-Kutta 4 (RK4):** A fourth-order numerical integration method that provides significantly higher accuracy under the same time-step conditions.

### Observation

The Euler method shows noticeable deviations from the analytical solution as the simulation progresses, while RK4 closely follows the analytical solution throughout the simulation.

This comparison demonstrates the difference in numerical accuracy between first-order and fourth-order integration methods.

<div align="center">

![ODE2 Numerical Integration Comparison](https://github.com/user-attachments/assets/4e1cf303-4a50-4b9a-b763-80490980ec79)

</div>
