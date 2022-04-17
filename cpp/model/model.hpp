//
//  model.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#pragma once

#include <vector>
#include "gurobi_c++.h"

using varMatrix = std::vector<vector<GRBVar>>;
using varArray  = std::vector<GRBVar>;
using numMatrix = std::vector<vector<double>>;

class Model
{
    struct Edge
    {
        int from;
        int to;
        double dist;
    };
        
    std::vector<Edge>             const d_edges;
    std::vector<std::vector<int>> const d_tileSets;
    
    int const d_idx_inst;
    int const d_nNodes;
    
    // Gurobi variables
    
    GRBEnv   d_env;
    GRBModel d_model;
    
    varMatrix d_x;
    varArray  d_u;
    
public:
    Model(int idx_inst, int runtime);
    
    void solve(int solvingTime);
    void printSolution() const;
    
    void exportSolution() const;
    
private:
    std::vector<Edge> read_edges(int idx_inst) const;
    std::vector<std::vector<int>> read_tileSets(int idx_inst) const;
    
    int get_nNodes() const;
    
    void createVariables();
    void createObjective();
    void createConstraints();
    
    void createConstraints_MTZ();
    
    // Helper functions
    
    bool edgeExists (int idx, int jdx) const;
    bool inTile (int idx_node, vector<int> const &tileSet) const;
};



inline int Model::get_nNodes() const
{
    int maxVal = 0;
    
    for (Edge const &e: d_edges)
        maxVal = max(maxVal, max(e.from, e.to));
        
    return maxVal + 1;
}

inline bool Model::edgeExists (int idx, int jdx) const
{
    for (Edge const &e: d_edges)
        if (e.from == idx && e.to == jdx)
            return true;
    
    return false;
}

inline bool Model::inTile (int idx_node, vector<int> const &tileSet) const
{
    for (int v: tileSet)
        if (v == idx_node)
            return true;
    
    return false;
}
