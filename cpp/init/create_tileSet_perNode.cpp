//
//  create_tileSet_perNode.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::create_tileSet_perNode()
{
    d_tileSets_perNode = vector<int>(d_nNodes, -1);
    
    for (int idx_tile = 0; idx_tile < d_nTileSets; ++idx_tile)
        for (int const idx_node: d_tileSets_perTile[idx_tile])
            d_tileSets_perNode[idx_node] = idx_tile;
}
