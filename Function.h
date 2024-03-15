#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>
#include "Area.h"

class Function
{
protected:
    int dim;
    std::vector<double> x;
    double f;

public:
    Function();
    virtual ~Function();
    explicit Function(const int dimension);
    int get_dim();
    std::vector<double> get_x();
    double get_f();
    std::vector<double> gradient(std::vector<double> x_, double h, const Area& a);
    std::vector<std::vector<double>> hessian(std::vector<double> x_, double h, const Area& a);

    virtual double calculate(std::vector<double> x) = 0;
};

class Function1 : public Function {
public:
    Function1();
    double calculate(std::vector<double> x_) override;
};


class Function2 : public Function {
public:
    Function2();
    double calculate(std::vector<double> x_) override;
};


class Function3 : public Function {
public:
    Function3();
    double calculate(std::vector<double> x_) override;
};
