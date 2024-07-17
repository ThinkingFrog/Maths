#pragma once

struct Config {
  const double LEFT = 1;
  const double RIGHT = 2;
  const double A = 0;
  const double B = 1;
  const double C = 1;
  const double D = 0;
  const double alpha = 0;
  const double beta = 0.5;
  unsigned N;
  double h;

  double error1 = 0;
  double error2 = 0;
};