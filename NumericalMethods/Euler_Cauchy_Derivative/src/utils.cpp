#include <vector>

#include "config.h"
#include "solver.h"
#include "utils.h"

void fill_grid(std::vector<double> &grid, Config &cfg) {
  for (unsigned idx = 0; idx <= cfg.N; idx++)
    grid.push_back(cfg.left + idx * cfg.h);
}

double next_y(double x, double y, double h) {
  double f = calc_precise_derivative(x, y);
  return y + h / 2.0 * (f + calc_precise_derivative(x + h, y + h * f));
}
