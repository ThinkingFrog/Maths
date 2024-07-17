#pragma once

#include <vector>

#include "config.h"

void fill_grid(std::vector<double> &grid, Config &cfg);

double next_y(double x, double y, double h);