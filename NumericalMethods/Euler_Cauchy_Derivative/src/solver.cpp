#include <cmath>
#include <vector>

#include "solver.h"
#include "utils.h"

// y = x(x^2 + 1)
double calc_precise_solution(double x) { return x * (x * x + 1); }

// y' = f(x,y) = x^2 + 1 + (2xy) / (x^2 + 1)
double calc_precise_derivative(double x, double y) {
  return x * x + 1 + (2 * x * y) / (x * x + 1);
}

//(x^2 + 1)y'- 2xy = (x^2 + 1)^2
unsigned calc_solution(std::vector<double> xi, std::vector<double> &y_i,
                       Config &cfg) {
  y_i.push_back(cfg.y_left);
  double y1, y2;
  unsigned j_max = 0;

  for (unsigned i = 1; i <= cfg.N; i++) {
    y1 = 100.0;
    y2 = next_y(xi[i - 1], y_i[i - 1], cfg.h);

    unsigned j;
    for (j = 1; fabs(y1 - y2) / 3 > cfg.eps;) {
      y1 = y2;
      j *= 2;
      y2 = y_i[i - 1];
      for (unsigned k = 0; k < j; ++k)
        y2 = next_y(xi[i - 1] + cfg.h * k / j, y2, cfg.h / j);
    }

    if (j_max < j)
      j_max = j;

    y_i.push_back(y2);
  }

  return j_max;
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
