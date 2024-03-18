#include "Area.h"


Area::Area() {};
Area::Area(const std::vector<std::pair<double, double>>& box_): box(box_) {}

std::vector<std::pair<double, double>> Area::get_box() {
    return box;
}

void Area::set_box(const double min, const double max) {
    box.clear();
    box.push_back(std::make_pair(min, max));
}

bool Area::is_inside(std::vector<double> x) const {
    if (x.size() != box.size()) 
        return false;

    for (size_t i = 0; i < x.size(); ++i) {
        if (x[i] > box[i].second || x[i] < box[i].first) 
            return false;
    }
    return true;
}

