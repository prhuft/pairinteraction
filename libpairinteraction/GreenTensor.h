/*
 * Copyright (c) 2016 Sebastian Weber, Henri Menke, Johannes Block. All rights reserved.
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

#ifndef GREENTENSOR_H
#define GREENTENSOR_H

#include <Eigen/Sparse>
#include <unsupported/Eigen/CXX11/Tensor>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <fstream> //um Datei zu erzeugen, zu Testzwecken
#include <iomanip>
#include <ios>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

class GreenTensor {

public:

    void vacuumDipoleQuadrupole(double x, double z); // TODO create vacuum(x,z,order), include order-parameter in constructor.
    void plateDipoleQuadrupole(double x, double zA, double zB);
    void addSurface(double d);
    GreenTensor(double x, double y, double z);
//     GreenTensor(double x, double zA, double zB);
    const Eigen::Matrix<double, 3, 3> &getDDTensor();
private:
    double x;
    double y;
    double z;
    double angle;
    double zA;
    double zB;

    bool dd_tensor_calculated;
    bool dq_tensor_calculated;
    double surface_distance;

    double KDelta(int i, int j);
    void vacuum(double x, double y, double z);
    void plate(double x, double zA, double zB);

    Eigen::Matrix<double, 3, 3> dd_tensor;
    Eigen::Tensor<double,3> qd_tensor;
    Eigen::Tensor<double,3> dq_tensor;

};

#endif
