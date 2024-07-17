#pragma once

#include <vector>

#include "config.h"

double calc_precise_solution(double x);

double calc_precise_derivative(double x, double y);

unsigned calc_solution(std::vector<double> xi, std::vector<double> &y_i,
                       Config &cfg);

double calc_max_err(std::vector<double> y, std::vector<double> yi);