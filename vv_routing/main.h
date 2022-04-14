//
//  main.h
//  vv_routing
//
//  Created by Michiel uit het Broek on 13/04/2022.
//

#ifndef main_h
#define main_h

using namespace std;

#include <iostream>
#include <fstream>

#include <vector>


#include "gurobi_c++.h"

struct Edge
{
    int from;
    int to;
    double dist;
};

void model1();
vector<Edge> read_edges();
vector<vector<int>> read_tileSets();


#endif
