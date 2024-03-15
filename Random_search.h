#pragma once
#include "Function.h"
#include "Area.h"
#include "Stop_criterion.h"
#include "Optimization_method.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>

class Random_search :
    public Optimization_method
{
private:
    unsigned seed;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
    double p;
    double delta, curr_delta;
    double alpha;

public:
    Random_search();
    Random_search(Function* function, std::vector<double> x_0, Area area,
        Stop_criterion* stop_criterion, double p_ = 0.5, double delta_ = 1, double alpha_ = 1);

    void optimization() override;
};
