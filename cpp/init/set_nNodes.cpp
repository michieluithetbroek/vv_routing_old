//
//  set_nNodes.cpp
//  vv_routing
//
// Loop over the tile sets to find the number of nodes
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::set_nNodes()
{
    int maxVal = 0;
    
    for (auto const &tileSet: d_tileSets_perTile)
        for (int const idx_node: tileSet)
          maxVal = max(maxVal, idx_node);
        
    d_nNodes = maxVal + 1;
}
