#pragma once

struct Config {
  double left = 0;
  double right = 2;
  double y_left = 0;
  double N = 20;
  double h = (right - left) / N;
  double eps = 1e-1;
};