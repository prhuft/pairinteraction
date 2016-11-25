/*
 * Copyright (c) 2016 Sebastian Weber, Henri Menke. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WAVEFUNCTION_HPP
#define WAVEFUNCTION_HPP

#include <string>
#include <vector>
#include "dtypes.h"
#include "QuantumDefect.h"

// --- Common interface ---

class Wavefunction {
protected:
  QuantumDefect qd;
  int nsteps_;
  real_t xmin_;
  real_t xmax_;
  real_t dx_;
  std::vector<real_t> x;
  std::vector<real_t> y;
  void initialize(double xmin);
public:
  const int &nsteps;
  const real_t &xmin;
  const real_t &xmax;
  const real_t &dx;
  Wavefunction(const QuantumDefect &qd)
    : qd(qd),
      nsteps(nsteps_), xmin(xmin_), xmax(xmax_), dx(dx_) {};
  std::vector<real_t> axis();
  std::vector<real_t> integrate();
};

// --- Numerov's method ---

class Numerov : public Wavefunction {
private:
  real_t V(real_t x);
  real_t g(real_t x);
  real_t step(int i);
public:
  Numerov(const QuantumDefect &qd);
  std::vector<real_t> axis();
  std::vector<real_t> integrate();
};

// --- Whittaker method ---

class Whittaker : public Wavefunction {
public:
  Whittaker(const QuantumDefect &qd);
  std::vector<real_t> axis();
  std::vector<real_t> integrate();
};

// --- Matrix element calculation ---

size_t findidx(std::vector<real_t> x, real_t d);


template<typename T>
real_t IntegrateRadialElement(T N1, int power, T N2) {
    std::vector<real_t> x1 = N1.axis();
    std::vector<real_t> y1 = N1.integrate();
    std::vector<real_t> x2 = N2.axis();
    std::vector<real_t> y2 = N2.integrate();

    real_t xmin = N1.xmin >= N2.xmin ? N1.xmin : N2.xmin;
    real_t xmax = N1.xmax <= N2.xmax ? N1.xmax : N2.xmax;

    real_t mu = 0;
    // If there is an overlap, calculate the matrix element
    if (xmin <= xmax) {
        int start1 = findidx(x1, xmin);
        int end1   = findidx(x1, xmax);
        int start2 = findidx(x2, xmin);
        int end2   = findidx(x2, xmax);

        int i1, i2;
        for (i1 = start1, i2 = start2; i1 < end1 && i2 < end2; i1++, i2++) {
            mu += y1[i1]*y2[i2] * pow(x1[i1], 2*power+2) * N1.dx;
        }
        mu = fabs(2*mu);
    }

    return mu;
}

#endif // WAVEFUNCTION_HPP
