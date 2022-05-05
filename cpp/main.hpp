//
//  main.h
//  vv_routing
//
//  Created by Michiel uit het Broek on 13/04/2022.
//

#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "init/init.hpp"
#include "ALNS/Heuristic.hpp"
#include "model/model.hpp"
#include "IO_functions/IO_functions.hpp"

#include "gurobi_c++.h"

#include <os/log.h>
#include <os/signpost.h>

using namespace std;

void model1();

