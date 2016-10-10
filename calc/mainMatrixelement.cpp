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

#include "MatrixElements.h"
#include "QuantumDefect.h"
#include "State.h"
#include "Basisnames.h"

#include <getopt.h>
#include <sstream>
#include <string>
#include <limits>
#include <boost/filesystem.hpp>

// ############################################################################
// ### MAIN LOOP ##############################################################
// ############################################################################

int main(int argc, char **argv) {
    std::cout << std::unitbuf;

    size_t precision = std::numeric_limits<real_t>::digits10 + 1;

    std::string element = "";
    StateOne state_row;
    StateOne state_col;
    int power = 0;

    int c;
    opterr = 0;
    while((c = getopt (argc, argv, "e:r:c:p:")) != -1) {
        switch (c) {
        case 'e':
            element = optarg;
            break;
        case 'r':
            std::stringstream(optarg) >> state_row.n >> state_row.l >> state_row.j >> state_row.m;
            break;
        case 'c':
            std::stringstream(optarg) >> state_col.n >> state_col.l >> state_col.j >> state_col.m;
            break;
        case 'p':
            power = atoi(optarg);
            break;
        default:
            return 1;
        }
    }

    std::cout << element << std::endl;
    std::cout << state_row << std::endl;
    std::cout << state_col << std::endl;
    std::cout << power << std::endl;

    std::vector<StateOne> states({{state_row, state_col}});
    auto basis = std::make_shared<BasisnamesOne>(BasisnamesOne::fromStates(states));
    MatrixElements matrixelement(element, "");

    matrixelement.precalculateRadial(basis, power);
    real_t val = matrixelement.getRadial(state_row, state_col, power);
    std::cout << ">>RES" << std::setprecision(precision) << val << std::endl;

    return 0;

    /*size_t precision = std::numeric_limits<real_t>::digits10 + 1;

    if (str_row != "" and str_col != "") { // Dipole matrix element
        std::stringstream ss_row(str_row);
        std::stringstream ss_col(str_col);

        StateOne state_row, state_col;
        state_row.m = 0;
        state_col.m = 0;
        ss_row >> state_row.n >> state_row.l >> state_row.j >> state_row.m;
        ss_col >> state_col.n >> state_col.l >> state_col.j >> state_col.m;

        real_t dipolematrixelement = 0;
        if (selectionRulesMultipole(state_row, state_col, 1, state_row.m-state_col.m)) {
            MatrixElements matrixelement("Rb", "");
            std::vector<StateOne> states({{state_row, state_col}});
            auto basis = std::make_shared<BasisnamesOne>(BasisnamesOne::fromStates(states));
            matrixelement.precalculateMultipole(basis, 1);
            dipolematrixelement = matrixelement.getMultipole(state_row, state_col, 1);
        }

        std::cout << std::setprecision(precision) << dipolematrixelement << std::endl;

    } else if (str_row != "" or str_col != "") {
        std::stringstream ss;
        if (str_row != "") { // Energy of row state
            ss << str_row;
        } else { // Energy of columne state
            ss << str_col;
        }

        StateOne state;
        ss >> state.n >> state.l >> state.j >> state.m;

        real_t energy = energy_level("Rb", state.n, state.l, state.j);

        std::cout << std::setprecision(precision) << energy << std::endl;
    }

    return 0;*/
}
