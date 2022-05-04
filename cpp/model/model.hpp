//
//  model.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#pragma once

#include <vector>
#include <random>

#include "./../init/init.hpp"

#include "gurobi_c++.h"

using varMatrix = std::vector<std::vector<GRBVar>>;
using varArray  = std::vector<GRBVar>;
using numMatrix = std::vector<std::vector<double>>;

class Model
{
public:
        
    int const d_idx_inst;
    int const d_nNodes;
    
    std::vector<Edge>             const d_edges;
    std::vector<std::vector<int>> const d_tileSets;
    
    // Gurobi variables
    
    GRBEnv   d_env;
    GRBModel d_model;
    
    varMatrix d_x;
    varArray  d_u;
    
public:
    Model(Init const init, int runtime);
    
    void solve(int solvingTime);
    
    void printSolution() const;

    void exportSolution() const;
    
    int nextNode (std::vector<std::vector<double>> const &x, int const curr_node) const;
    
    
    
private:
    void createVariables();
    void createObjective();
    void createConstraints();
    
    void createConstraints_oneWay();
    void createConstraints_MTZ();
    
    void setInitialSolution();
    
    int getNodeFromTile(int idx_tile, std::mt19937_64 &gen) const;
    
    // Helper functions
    
    bool edgeExists (int idx, int jdx) const;
    bool inTile (int idx_node, std::vector<int> const &tileSet) const;
    
    double getCost (int idx_from, int idx_to) const;
};

inline double Model::getCost (int idx_from, int idx_to) const
{
    for (Edge const &e: d_edges)
        if (e.from == idx_from && e.to == idx_to)
            return e.dist;
    
    std::cout << idx_from << " - " << idx_to << std::endl;
    
    throw std::string("Model::getCost - Edge does not exist");
}

inline bool Model::edgeExists (int idx, int jdx) const
{
    for (Edge const &e: d_edges)
        if (e.from == idx && e.to == jdx)
            return true;
    
    return false;
}

inline bool Model::inTile (int idx_node, std::vector<int> const &tileSet) const
{
    for (int v: tileSet)
        if (v == idx_node)
            return true;
    
    return false;
}

inline int Model::nextNode (std::vector<std::vector<double>> const &x, int const curr_node) const
{
    int idx = -1;
    while (x[curr_node][++idx] < 0.5);
    
    return idx;
}
