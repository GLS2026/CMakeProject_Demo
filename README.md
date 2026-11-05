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
**Build:** Execute NumericalProject under `wrapper`
```
#Linux
./main/NumericalProject
../install/bin/NumericalProject
#windows
main\NumericalProject
..\install\bin\NumericalProject
```
**Validate:**

1. Execute `ctest` under `wrapper`
2. Execute `test_math` under the root
```
#linux
cd install/bin
#windows
cd install\bin

test_math
```

**Animaion:** execute in python environment after build
```
cd tests
python animation.py
```

## About Mass-Damper-Spring System

The Mass-Damper-Spring system is a classical second-order mechanical system consisting of a mass, a damper, and a spring. Its dynamic behavior is described by Newton's Second Law.

#### 1. Mathematical Model

Consider a mass connected to a spring and a damper, subject to an external force $F(t)$.

The forces acting on the mass are:

- **External force:** $F(t)$
- **Damping force:** $-c\dot{x}(t)$
- **Spring force:** $-kx(t)$

According to Newton's Second Law:

$$
\sum F = m\ddot{x}(t)
$$

Therefore, the governing second-order differential equation is:

$$
\displaystyle
\boxed{
m\ddot{x}(t)+c\dot{x}(t)+kx(t)=F(t)
}
$$

Where:

<table>
  <tr>
    <td width="50%" valign="middle">

| Parameter | Value |
|:---|---:|
| Mass ($m$) | 1.0 kg |
| Damping ($c$) | 0.5 Ns/m |
| Stiffness ($k$) | 4.0 N/m |
| Initial position ($x_0$) | 1.0 m |
| Initial velocity ($v_0$) | 0.0 m/s |
| External force ($F_0$) | 10 N |

</td>
    <td width="50%" align="center" valign="middle">
      <img src="https://github.com/user-attachments/assets/7a916997-a146-408f-a1aa-283e2940536c" width="420" alt="Mass-Damper-Spring System">
    </td>
  </tr>
</table>

#### 2. State Equation Derivation

To solve the second-order differential equation numerically, we convert it into a system of first-order differential equations.

Define the state variables:

$$
\displaystyle
x_1(t)=x(t)
$$

$$
\displaystyle
x_2(t)=\dot{x}(t)
$$

Taking the derivative of each state variable:

$$
\displaystyle
\dot{x}_1(t)=x_2(t)
$$

From the original differential equation:

$$
\displaystyle
\ddot{x}(t)=
\frac{F(t)-c\dot{x}(t)-kx(t)}{m}
$$

Thus:

$$
\displaystyle
\dot{x}_2(t)=
\frac{F(t)-cx_2(t)-kx_1(t)}{m}
$$

Combining both equations gives the **State Equation**:

$$
\begin{aligned}
\begin{bmatrix}
\dot{x}_1 \\
\dot{x}_2
\end{bmatrix}
&=
\begin{bmatrix}
0 & 1 \\
-\frac{k}{m} & -\frac{c}{m}
\end{bmatrix}
\begin{bmatrix}
x_1 \\
x_2
\end{bmatrix}
+
\begin{bmatrix}
0 \\
\frac{1}{m}
\end{bmatrix}
F(t)
\end{aligned}
$$

In compact form:

$$
\boxed{\dot{\mathbf{x}}=A\mathbf{x}+B F(t)}
$$

Where:

$$
\mathbf{x}=
\begin{bmatrix}
x_1 \\ x_2
\end{bmatrix}
$$

$$
A=
\begin{bmatrix}
0 & 1 \\
-\frac{k}{m} & -\frac{c}{m}
\end{bmatrix}
$$

$$
B=
\begin{bmatrix}
0 \\ \frac{1}{m}
\end{bmatrix}
$$

The initial state is:

$$
\mathbf{x}(0)=
\begin{bmatrix}
x_0 \\ v_0
\end{bmatrix}
$$

This state-space representation allows numerical integration methods such as Euler's Method and the Fourth-Order Runge-Kutta (RK4) Method to solve the system.

#### 3. Analytical Solution (Constant External Force)

For comparison with numerical integration, we derive the analytical solution under a constant external force:

$$
F(t)=F_0
$$

The governing equation becomes:

$$
m\ddot{x}+c\dot{x}+kx=F_0
$$

**Step 1: Determine the equilibrium position**

At equilibrium, velocity and acceleration are both zero:

$$
kx_{eq}=F_0
$$

Therefore:

$$
\boxed{x_{eq}=\frac{F_0}{k}}
$$

**Step 2: Transform into a homogeneous differential equation**

Define the displacement relative to equilibrium:

$$
u(t)=x(t)-x_{eq}
$$

Since $x_{eq}$ is constant:

$$
\dot{u}(t)=\dot{x}(t)
$$

$$
\ddot{u}(t)=\ddot{x}(t)
$$

Substituting into the original equation gives:

$$
m\ddot{u}+c\dot{u}+ku=0
$$

This is the homogeneous second-order differential equation.

**Step 3: Determine the damping characteristics**

Define the natural frequency:

$$
\omega_n=\sqrt{\frac{k}{m}}
$$

Define the damping ratio:

$$
\zeta=\frac{c}{2\sqrt{mk}}
$$

For an underdamped system:

$$
0\leq\zeta<1
$$

The damped natural frequency is:

$$
\boxed{
\omega_d=\omega_n\sqrt{1-\zeta^2}
}
$$

**Step 4: Derive the displacement solution**

The general solution for an underdamped system is:

$$
u(t)=e^{-\zeta\omega_n t}
\left[
C_1\cos(\omega_d t)+
C_2\sin(\omega_d t)
\right]
$$

Since $x(t)=u(t)+x_{eq}$, the displacement becomes:

$$
x(t)=x_{eq}+e^{-\zeta\omega_n t}
\left[
C_1\cos(\omega_d t)+
C_2\sin(\omega_d t)
\right]
$$

**Step 5: Determine the integration constants using initial conditions**

Given:

$$
x(0)=x_0,\qquad \dot{x}(0)=v_0
$$

At $t=0$:

$$
\boxed{C_1=x_0-x_{eq}}
$$

Differentiating the displacement equation and applying the initial velocity:

$$
v_0=-\zeta\omega_n C_1+\omega_d C_2
$$

Therefore:

$$
\boxed{
C_2=\frac{v_0+\zeta\omega_n C_1}{\omega_d}
}
$$

**Step 6: Final analytical solution**

Substituting the constants gives the displacement:

$$
\boxed{
x(t)=x_{eq}+e^{-\zeta\omega_n t}
\left[
C_1\cos(\omega_d t)+
C_2\sin(\omega_d t)
\right]
}
$$

The velocity is obtained by differentiating the displacement:

$$
\begin{aligned}
\dot{x}(t)=e^{-\zeta\omega_n t}\Big[&
(-\zeta\omega_n C_1+\omega_d C_2)
\cos(\omega_d t)\\
&-(\zeta\omega_n C_2+\omega_d C_1)
\sin(\omega_d t)
\Big]
\end{aligned}
$$

The analytical solution provides the reference values for evaluating the accuracy of numerical integration methods.

#### 4. Numerical Example

Using the following system parameters:

| Parameter | Value |
|---|---:|
| Mass $m$ | 1.0 kg |
| Damping $c$ | 0.5 N·s/m |
| Stiffness $k$ | 4.0 N/m |
| Initial position $x_0$ | 1.0 m |
| Initial velocity $v_0$ | 0.0 m/s |
| External force $F_0$ | 10.0 N |

The equilibrium position is:

$$
x_{eq}=\frac{10}{4}=2.5\text{ m}
$$

The natural frequency, damping ratio, and damped natural frequency are:

$$
\omega_n=2
$$

$$
\zeta=0.125
$$

$$
\omega_d\approx1.98431
$$

The integration constants are:

$$
C_1=1.0-2.5=-1.5
$$

$$
C_2\approx-0.09450
$$

Therefore, the analytical displacement and velocity can be evaluated at any time $t$, and compared against the Euler and RK4 numerical solutions.

**Note:** This analytical solution assumes a constant external force and an underdamped system. It is not a general closed-form solution for arbitrary time-varying external forces.

## ODE2 Numerical Integration Results
### Mass-Damper-Spring System with Numerical Analysis

The following figure compares the analytical solution (Real) of the mass-damper-spring system with the numerical solutions obtained using the Euler method and the fourth-order Runge-Kutta method (RK4).

- **Analytical Solution (Real):** The theoretical solution used as the reference for numerical accuracy.
- **Euler Method:** A first-order numerical integration method. Its accumulated numerical error becomes increasingly noticeable over time.
- **Runge-Kutta 4 (RK4):** A fourth-order numerical integration method that provides significantly higher accuracy under the same time-step conditions.

### Observation

The Euler method shows noticeable deviations from the analytical solution as the simulation progresses, while RK4 closely follows the analytical solution throughout the simulation.

This comparison demonstrates the difference in numerical accuracy between first-order and fourth-order integration methods.

<div align="center">

![ODE2 Numerical Integration Comparison](https://github.com/user-attachments/assets/4e1cf303-4a50-4b9a-b763-80490980ec79)

</div>
