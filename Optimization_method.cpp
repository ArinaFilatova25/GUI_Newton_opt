#include "Optimization_method.h"
#include "Function.h"
#include "Stop_criterion.h"

Optimization_method::Optimization_method(){}

Optimization_method::~Optimization_method() {
    delete function;
    delete stop_criterion;
}

Optimization_method::Optimization_method(Function* func, std::vector<double> x_0, Area area_, Stop_criterion* stop_crit_) :
    function(func), area(area_), stop_criterion(stop_crit_), num_of_iter(0), num_of_iter_since_last_approx(0) {
    seq_x_i.push_back(x_0);
    seq_f_i.push_back(function->calculate(x_0));
}

std::vector<std::vector<double>> Optimization_method::get_seq_x_i() {
    return seq_x_i;
}

std::vector<double> Optimization_method::get_seq_f_i() {
    return seq_f_i;
}

Function* Optimization_method::get_function() {
    return function;
}

Area Optimization_method::get_area() {
    return area;
}

Stop_criterion* Optimization_method::get_stop_criterion() {
    return stop_criterion;
}

int Optimization_method::get_num_of_iter() {
    return num_of_iter;
}

int Optimization_method::get_num_of_iter_since_last_approx() {
    return num_of_iter_since_last_approx;
}
