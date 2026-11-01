#ifndef ODE_FUNCTION_H
#define ODE_FUNCTION_H

// Parent Class
class ODEFunction {
public:
    virtual ~ODEFunction() = default;
    virtual double derivative(double t, double y) const = 0;
    virtual double exact_solution(double t) const = 0;

    // Initial conditions
    virtual double initial_x() const = 0;
    virtual double initial_y() const = 0;
};

// Child Class
class ODE1 : public ODEFunction {
public:
    double derivative(double t, double y) const override;
    double exact_solution(double t) const override;

    double initial_x() const override;
    double initial_y() const override;
};
#endif