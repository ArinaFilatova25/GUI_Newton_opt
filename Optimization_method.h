class Function;
class Stop_criterion;

#pragma once
#include "Function.h"
#include "Area.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>


class Optimization_method {
protected:
    std::vector<std::vector<double>> seq_x_i;
    std::vector<double> seq_f_i;
    Function* function;
    Area area;
    Stop_criterion* stop_criterion;
    int num_of_iter;
    int num_of_iter_since_last_approx;

public:
    Optimization_method();
    virtual ~Optimization_method();
    Optimization_method(Function* func, std::vector<double> x_0, Area area_, Stop_criterion* stop_crit_);
    std::vector<std::vector<double>> get_seq_x_i();
    std::vector<double> get_seq_f_i();
    Function* get_function();
    Area get_area();
    Stop_criterion* get_stop_criterion();
    int get_num_of_iter();
    int get_num_of_iter_since_last_approx();

    virtual void optimization() = 0;
};
