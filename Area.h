#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>

class Area
{
private:
    std::vector<std::pair<double, double>> box;

public:
    Area();
    Area(const std::vector<std::pair<double, double>>& box_);
    std::vector<std::pair<double, double>> get_box();
    void set_box(const double min, const double max);
    bool is_inside(std::vector<double> x) const;
};

