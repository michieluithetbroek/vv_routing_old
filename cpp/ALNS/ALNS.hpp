//
//  ALNS.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#pragma once

#include <stdio.h>
#include <vector>

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
    
    // Initial solutions
    
    void initial_random (bool const printRoutes);
    void initial_CFI_A  (bool const printRoutes);
    void initial_CFI_A2 (bool const printRoutes);
    void initial_CFI_B  (bool const printRoutes);
    
public:
    ALNS(Init const init);
    
private:
    
};
