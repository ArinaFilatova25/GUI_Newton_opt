#include "Function.h"

Function::Function() {}

Function::~Function() {}

Function::Function(const int dimension) : dim(dimension) {}

int Function::get_dim() {
    return dim;
}

std::vector<double> Function::get_x() {
    return x;
}

double Function::get_f() {
    return f;
}


Function1::Function1() : Function(2) {}

double Function1::calculate(std::vector<double> x_) {
    x = x_;
    f = (x[0] + 2 * x[1] - 7) * (x[0] + 2 * x[1] - 7) + 
        (2 * x[0] + x[1] - 5) * (2 * x[0] + x[1] - 5);
    return f;
}

Function2::Function2() : Function(2) {}

double Function2::calculate(std::vector<double> x_) {
    x = x_;
    f = 0.26 * (x[0] * x[0] + x[1] * x[1]) - 0.48 * x[0] * x[1];
    return f;
}


Function3::Function3() : Function(2) {}

double Function3::calculate(std::vector<double> x_) {
    x = x_;
    f = 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]) + (x[0] - 1) * (x[0] - 1);
    return f;
}



std::vector<double> Function::gradient(std::vector<double> x_, double h, const Area& a) {
    int dim = get_dim();
    std::vector<double> result(dim, 0);
    std::vector<double> x_upper = x_, x_lower = x_;

    for (int i = 0; i < dim; ++i) {
        x_upper[i] += h;
        x_lower[i] -= h; 

        if (a.is_inside(x_upper)) {
            if (a.is_inside(x_lower)) {
                result[i] = (calculate(x_upper) - calculate(x_lower)) / (2 * h);
            }
            else {
                result[i] = (calculate(x_upper) - calculate(x_)) / h;
            }
        }
        else {
            result[i] = (calculate(x_) - calculate(x_lower)) / h;
        }

        x_upper[i] = x_[i];
        x_lower[i] = x_[i];
    }

    return result;
}


std::vector<std::vector<double>> Function::hessian(std::vector<double> x_, double h, const Area& a) {
    int dim = get_dim();
    std::vector<std::vector<double>> result(dim, std::vector<double>(dim, 0));
    std::vector<double> x_upper = x_, x_lower = x_;

    std::vector<double> grad_x = gradient(x_, h, a);
    std::vector<double> grad_x_upper = grad_x, grad_x_lower= grad_x;

    for (int i = 0; i < dim; ++i) {
        x_upper[i] += h;
        x_lower[i] -= h;

        grad_x_upper = gradient(x_upper, h, a);
        grad_x_lower = gradient(x_lower, h, a);

        for (int j = 0; j < dim; ++j) {

            if (a.is_inside(x_upper)) {
                if (a.is_inside(x_lower)) {
                    result[i][j] = (grad_x_upper[j] - grad_x_lower[j]) / (2 * h);
                }
                else {
                    result[i][j] = (grad_x_upper[j] - grad_x[j]) / h;
                }
            }
            else {
                result[i][j] = (grad_x[j] - grad_x_lower[j]) / h;
            }
        }

        x_upper[i] = x_[i];
        x_lower[i] = x_[i];
    }

    return result;
}



