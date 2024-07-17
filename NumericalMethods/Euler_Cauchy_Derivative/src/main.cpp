#include <fstream>
#include <iostream>
#include <vector>

#include "config.h"
#include "solver.h"
#include "utils.h"

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