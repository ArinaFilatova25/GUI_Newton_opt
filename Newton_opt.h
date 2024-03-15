#pragma once
#include "Function.h"
#include "Area.h"
#include <float.h>
#include <vector>
#include <chrono>
#include <random>
#include <sstream>
#include <cfloat>
#include "Stop_criterion.h"
#include "Optimization_method.h"
#include <Eigen/Dense>

class Newton_opt :
    public Optimization_method
{

public:
    Newton_opt();
    Newton_opt(Function* function, std::vector<double> x_0, Area area, Stop_criterion* stop_criterion);
    ~Newton_opt();

    void optimization() override;
};




