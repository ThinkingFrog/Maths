#pragma once

#include <vector>

#include "config.h"

void fill_x_grid(std::vector<double> &grid, Config &cfg);

void fill_supporting_vectors(std::vector<double> xi, std::vector<double> &pi,
                             std::vector<double> &qi, std::vector<double> &fi);

void fill_matrix_vectors(std::vector<double> pi, std::vector<double> qi,
                         std::vector<double> fi, std::vector<double> &bi,
                         std::vector<double> &ci, std::vector<double> &di,
                         std::vector<double> &ri, Config &cfg);

void fill_delta_vector(std::vector<double> bi, std::vector<double> ci,
                       std::vector<double> di, std::vector<double> &delta,
                       Config &cfg);

void fill_lambda_vector(std::vector<double> bi, std::vector<double> ci,
                        std::vector<double> ri, std::vector<double> delta,
                        std::vector<double> &lambda, Config &cfg);
