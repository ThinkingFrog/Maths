#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

#include "config.h"
#include "solver.h"

// y = ln(x)
double calc_precise_solution(double x) { return log(x); }

// xy''+y'+2y=2lnx
// y''+(1/x)y'+(2/x)y=(2ln(x)/x)
void calc_solution(std::vector<double> delta, std::vector<double> lambda,
                   std::vector<double> &y, Config &cfg) {
  for (int idx = cfg.N - 1; idx >= 0; --idx)
    if (idx == cfg.N - 1)
      y.push_back(lambda[cfg.N - 1]);
    else
      y.push_back(delta[idx] * y[cfg.N - idx - 2] + lambda[idx]);

  reverse(y.begin(), y.end());
}

double calc_max_err(std::vector<double> y, std::vector<double> yi) {
  double max_err = 0.0;

  for (unsigned i = 0; i < y.size(); ++i) {
    double err = fabs(y[i] - yi[i]);

    if (max_err < err)
      max_err = err;
  }

  return max_err;
}
