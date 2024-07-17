#pragma once

#include <vector>

#include "config.h"

double calc_precise_solution(double x);

void calc_solution(std::vector<double> delta, std::vector<double> lambda,
                   std::vector<double> &y, Config &cfg);

double calc_max_err(std::vector<double> y, std::vector<double> yi);