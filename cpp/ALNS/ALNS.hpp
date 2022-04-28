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
    int const d_nNodes;
    int const d_nTiles;
    
    std::vector<std::vector<double>> const d_cost;
    
    std::vector<std::vector<int>> const d_tileSets;
    
public:
    ALNS(Init const init);
    
private:
    
};
