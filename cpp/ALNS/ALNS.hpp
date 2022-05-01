//
//  ALNS.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <random>

#include "init.hpp"



class ALNS
{
    // Input data
    
    int const d_nNodes;
    int const d_nTiles;
    
    std::vector<std::vector<double>> const d_cost;
    
    std::vector<std::vector<int>> const d_tileSets_perTile;
    std::vector<int>              const d_tileSets_perNode;
    
    // Solution
    
    double d_currCost;
    std::vector<int> d_route;
    
    // Random generator
    
    std::mt19937 d_generator;
    
public:
    ALNS(Init const init);
    
private:
    
    // Initial solutions
    
    void initial_random (bool const printRoutes);
    void initial_CFI_A  (bool const printRoutes);
    void initial_CFI_A2 (bool const printRoutes);
    void initial_CFI_B  (bool const printRoutes);
    
    // Local search moves
    
    bool relocate ();
    bool relocate_tile();
    
    // Helper function
    
    double loopCost(std::vector<int> const &route) const;
    void printRoute() const;
};

inline void ALNS::printRoute() const
{
    for (int v: d_route)
        std::cout << v << " ";
    
    std::cout << '\n';
}

inline double ALNS::loopCost(std::vector<int> const &route) const
{
    size_t const n = size(route);
    
    double cost = d_cost[route[n - 1]][route[0]];
    
    for (int idx = 0; idx < n - 1; ++idx)
    {
        int from = route[idx];
        int to   = route[idx + 1];
        
        cost += d_cost[from][to];
    }
    
    return cost;
}
