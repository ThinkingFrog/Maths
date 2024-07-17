#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

#include "config.h"
#include "solver.h"
#include "utils.h"

void experiment_one(Config &cfg) {
  std::ofstream out_file;
  out_file.open("../output1.txt", std::ios::out | std::ios::trunc);

  for (cfg.N = 2; cfg.N <= 1e3; cfg.N++) {
    cfg.h = (cfg.RIGHT - cfg.LEFT) / (cfg.N - 1);

    std::vector<double> xi;
    fill_x_grid(xi, cfg);

    std::vector<double> y;
    for (auto x : xi)
      y.push_back(calc_precise_solution(x));

    std::vector<double> pi, qi, fi;
    fill_supporting_vectors(xi, pi, qi, fi);

    std::vector<double> bi, ci, di, ri;
    fill_matrix_vectors(pi, qi, fi, bi, ci, di, ri, cfg);

    std::vector<double> delta;
    fill_delta_vector(bi, ci, di, delta, cfg);

    std::vector<double> lambda;
    fill_lambda_vector(bi, ci, ri, delta, lambda, cfg);

    std::vector<double> yi;
    calc_solution(delta, lambda, yi, cfg);

    out_file << cfg.h << " " << calc_max_err(y, yi) << std::endl;
  }

  out_file.close();
}

void experiment_two(Config &cfg) {
  std::ofstream out_file;
  out_file.open("../output2.txt", std::ios::out | std::ios::trunc);

  for (cfg.error1 = 0.1; cfg.error1 > 1e-16; cfg.error1 /= 10) {
    std::vector<double> xi;
    fill_x_grid(xi, cfg);

    std::vector<double> y;
    for (auto x : xi)
      y.push_back(calc_precise_solution(x));

    std::vector<double> pi, qi, fi;
    fill_supporting_vectors(xi, pi, qi, fi);

    std::vector<double> bi, ci, di, ri;
    fill_matrix_vectors(pi, qi, fi, bi, ci, di, ri, cfg);

    std::vector<double> delta;
    fill_delta_vector(bi, ci, di, delta, cfg);

    std::vector<double> lambda;
    fill_lambda_vector(bi, ci, ri, delta, lambda, cfg);

    std::vector<double> yi;
    calc_solution(delta, lambda, yi, cfg);

    out_file << cfg.error1 << " " << calc_max_err(y, yi) << std::endl;
  }

  out_file.close();
}

void experiment_three(Config &cfg) {
  std::ofstream out_file;
  out_file.open("../output3.txt", std::ios::out | std::ios::trunc);

  for (cfg.error2 = 0.1; cfg.error2 > 1e-16; cfg.error2 /= 10) {
    std::vector<double> xi;
    fill_x_grid(xi, cfg);

    std::vector<double> y;
    for (auto x : xi)
      y.push_back(calc_precise_solution(x));

    std::vector<double> pi, qi, fi;
    fill_supporting_vectors(xi, pi, qi, fi);

    std::vector<double> bi, ci, di, ri;
    fill_matrix_vectors(pi, qi, fi, bi, ci, di, ri, cfg);

    std::vector<double> delta;
    fill_delta_vector(bi, ci, di, delta, cfg);

    std::vector<double> lambda;
    fill_lambda_vector(bi, ci, ri, delta, lambda, cfg);

    std::vector<double> yi;
    calc_solution(delta, lambda, yi, cfg);

    out_file << cfg.error2 << " " << calc_max_err(y, yi) << std::endl;
  }

  out_file.close();
}

int main() {
  Config cfg = Config();

  experiment_one(cfg);

  cfg.N = (unsigned)1e3;
  cfg.h = (cfg.RIGHT - cfg.LEFT) / (cfg.N - 1);

  experiment_two(cfg);

  cfg.error1 = 0;

  experiment_three(cfg);

  return 0;
}
