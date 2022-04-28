//
//  init.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#pragma once

#include <stdio.h>
#include <vector>
#include <string>

struct Edge
{
    int from;
    int to;
    double dist;
};

class Init
{
    int const d_defaultCost = 99999;
    
    std::vector<Edge> d_edges;
    
    std::vector<std::vector<double>> d_cost;
    std::vector<std::vector<int>> d_tileSets;
    
    std::string d_filePath;
    
    int d_nNodes;
    int d_nTilesX;
    int d_nTilesY;
    
public:
    Init(int idx_inst);
    
private:
    void read_edges();
    void read_tileSets();
    void set_nNodes();
    
    void create_costMatrix();
};
