#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

#include "config.h"
#include "utils.h"

void fill_x_grid(std::vector<double> &grid, Config &cfg) {
  for (unsigned idx = 0; idx < cfg.N; ++idx)
    grid.push_back(cfg.LEFT + idx * cfg.h);
}

void fill_supporting_vectors(std::vector<double> xi, std::vector<double> &pi,
                             std::vector<double> &qi, std::vector<double> &fi) {
  for (auto x : xi) {
    pi.push_back(1 / x);
    qi.push_back(2 / x);
    fi.push_back(2 * log(x) / x);
  }
}

void fill_matrix_vectors(std::vector<double> pi, std::vector<double> qi,
                         std::vector<double> fi, std::vector<double> &bi,
                         std::vector<double> &ci, std::vector<double> &di,
                         std::vector<double> &ri, Config &cfg) {
  for (unsigned idx = 0; idx < cfg.N; idx++)
    if (idx == 0) {
      bi.push_back(0);
      ci.push_back(cfg.h * cfg.B - cfg.A);
      di.push_back(cfg.A);
      ri.push_back(cfg.h * (cfg.alpha + cfg.error1));
    } else if (idx == cfg.N - 1) {
      bi.push_back(-ci[idx - 1] - 4 * bi[idx - 1]);
      ci.push_back(3 * bi[idx - 1] - di[idx - 1]);
      di.push_back(0);
      ri.push_back(2 * cfg.h * bi[idx - 1] * (cfg.beta + cfg.error2) -
                   ri[idx - 1]);
    } else {
      bi.push_back(1 - cfg.h / 2 * pi[idx]);
      ci.push_back(cfg.h * cfg.h * qi[idx] - 2);
      di.push_back(1 + cfg.h / 2 * pi[idx]);
      ri.push_back(cfg.h * cfg.h * fi[idx]);
    }
}

void fill_delta_vector(std::vector<double> bi, std::vector<double> ci,
                       std::vector<double> di, std::vector<double> &delta,
                       Config &cfg) {
  for (unsigned idx = 0; idx < cfg.N; ++idx)
    if (idx == 0)
      delta.push_back(-di[0] / ci[0]);
    else
      delta.push_back(-di[idx] / (ci[idx] + bi[idx] * delta[idx - 1]));
}

void fill_lambda_vector(std::vector<double> bi, std::vector<double> ci,
                        std::vector<double> ri, std::vector<double> delta,
                        std::vector<double> &lambda, Config &cfg) {
  for (unsigned idx = 0; idx < cfg.N; ++idx)
    if (idx == 0)
      lambda.push_back(ri[0] / ci[0]);
    else
      lambda.push_back((ri[idx] - bi[idx] * lambda[idx - 1]) /
                       (ci[idx] + bi[idx] * delta[idx - 1]));
}
