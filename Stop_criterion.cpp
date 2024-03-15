#include "Stop_criterion.h"
#include "Optimization_method.h"


Stop_criterion::Stop_criterion(): eps(0.001), max_num_of_iterations(100) {}

Stop_criterion::~Stop_criterion(){}

Stop_criterion::Stop_criterion(double eps_, int max_num_of_iterations_)
    : eps(eps_), max_num_of_iterations(max_num_of_iterations_) {}

double Stop_criterion::get_eps() {
    return eps;
}

int Stop_criterion::get_max_num_of_iterations() {
    return max_num_of_iterations;
}

Criterion_f_difference_min::Criterion_f_difference_min(){}

Criterion_f_difference_min::Criterion_f_difference_min(double eps_, int max_num_of_iterations_)
    : Stop_criterion(eps_, max_num_of_iterations_) {}

bool Criterion_f_difference_min::termination(Optimization_method* optimization_method) {
    int num_iter = optimization_method->get_seq_f_i().size();
    if (num_iter == 1)
        return false;

    if (num_iter >= max_num_of_iterations)
        return true;

    double curr_f = optimization_method->get_seq_f_i()[num_iter - 1],
           prev_f = optimization_method->get_seq_f_i()[num_iter - 2];
    return (std::abs(curr_f - prev_f )< eps);
}

Criterion_max_iter::Criterion_max_iter(){}

Criterion_max_iter::Criterion_max_iter(int max_num_of_iterations_)
    : Stop_criterion(0, max_num_of_iterations_) {}

bool Criterion_max_iter::termination(Optimization_method* optimization_method) {
    return optimization_method->get_num_of_iter() >= max_num_of_iterations;
}

Criterion_num_iter_last_approx::Criterion_num_iter_last_approx(){}

Criterion_num_iter_last_approx::Criterion_num_iter_last_approx(int max_num_of_iterations_)
    : Stop_criterion(0, max_num_of_iterations_) {}

bool Criterion_num_iter_last_approx::termination(Optimization_method* optimization_method) {
    return optimization_method->get_num_of_iter_since_last_approx() >= max_num_of_iterations;
}

Criterion_grad_f::Criterion_grad_f(){}

Criterion_grad_f::Criterion_grad_f(double eps_, int max_num_of_iterations_)
    : Stop_criterion(eps_, max_num_of_iterations_) {}

bool Criterion_grad_f::termination(Optimization_method* optimization_method) {
    if (optimization_method->get_num_of_iter() >= max_num_of_iterations)
        return true;

    std::vector<double> grad = optimization_method->get_function()->gradient(optimization_method->get_seq_x_i().back(), eps/10, optimization_method->get_area());
    int dim = optimization_method->get_function()->get_dim();
    double grad_sum_sq = 0;
    for (int i = 0; i < dim; ++i) {
        grad_sum_sq += grad[i] * grad[i];
    }
    return (std::sqrt(grad_sum_sq) < eps);
}

Criterion_x_difference::Criterion_x_difference(){}

Criterion_x_difference::Criterion_x_difference(double eps_, int max_num_of_iterations_)
    : Stop_criterion(eps_, max_num_of_iterations_) {}

bool Criterion_x_difference::termination(Optimization_method* optimization_method) {

    std::vector<std::vector<double>> seq_x_i = optimization_method->get_seq_x_i();
    int size = seq_x_i.size();

    if (size == 1)
        return false;

    if (optimization_method->get_num_of_iter() >= max_num_of_iterations)
        return true;

    int dim = optimization_method->get_function()->get_dim();
    std::vector<double> x1 = seq_x_i[size - 1], x2 = seq_x_i[size - 2];

    double x_sum_sq = 0;
    for (int i = 0; i < dim; ++i) {
        x1[i] -= x2[i];
        x_sum_sq += x1[i] * x1[i];
    }
    return (std::sqrt(x_sum_sq) < eps);
}

Criterion_f_difference::Criterion_f_difference(){}

Criterion_f_difference::Criterion_f_difference(double eps_, int max_num_of_iterations_)
    : Stop_criterion(eps_, max_num_of_iterations_) {}

bool Criterion_f_difference::termination(Optimization_method* optimization_method) {

    std::vector<double> seq_f_i = optimization_method->get_seq_f_i();
    int size = seq_f_i.size();

    if (size == 1)
        return false;

    if (optimization_method->get_num_of_iter() >= max_num_of_iterations)
        return true;

    return (std::abs((seq_f_i[size - 1] - seq_f_i[size - 2]) / seq_f_i[size - 1]) < eps);
}
