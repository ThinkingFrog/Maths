#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

struct Config {
  double left = 0;
  double right = 2;
  double y_left = 0;
  double N = 20;
  double h = (right - left) / N;
  double eps = 1e-1;
};

// y = x(x^2 + 1)
inline double calc_precise_solution(double x) { return x * (x * x + 1); }

// y' = f(x,y) = x^2 + 1 + (2xy) / (x^2 + 1)
double calc_precise_derivative(double x, double y) {
  return x * x + 1 + (2 * x * y) / (x * x + 1);
}

void fill_grid(std::vector<double> &grid, Config &cfg) {
  for (unsigned idx = 0; idx <= cfg.N; idx++)
    grid.push_back(cfg.left + idx * cfg.h);
}

double next_y(double x, double y, double h) {
  double f = calc_precise_derivative(x, y);
  return y + h / 2.0 * (f + calc_precise_derivative(x + h, y + h * f));
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

int main(void) {
  Config cfg = Config();
  double eps;
  double y_left = cfg.y_left;

  std::vector<double> xi;
  fill_grid(xi, cfg);

  std::vector<double> y;
  for (auto x : xi)
    y.push_back(calc_precise_solution(x));

  std::ofstream file1, file2, file3;
  file1.open("../output1.txt", std::ios::out | std::ios::trunc);
  file2.open("../output2.txt", std::ios::out | std::ios::trunc);
  file3.open("../output3.txt", std::ios::out | std::ios::trunc);

  for (eps = 1e-1; eps > 1e-13; eps /= 10) {
    std::vector<double> yi;
    unsigned iters = calc_solution(xi, yi, cfg);

    file1 << eps << " " << calc_max_err(y, yi) << std::endl;
    file2 << eps << " " << iters << std::endl;
  }

  eps = 1e-5;
  for (y_left = 0.1; y_left > 1e-10; y_left /= 10) {
    std::vector<double> yi;
    calc_solution(xi, yi, cfg);

    file3 << y_left << " " << calc_max_err(y, yi) << std::endl;
  }

  file1.close();
  file2.close();
  file3.close();

  return 0;
}