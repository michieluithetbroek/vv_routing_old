//
//  getNodeFromTile.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 23/04/2022.
//

#include "model.ih"

int Model::getNodeFromTile(int idx_tile) const
{
    auto const &tile = d_tileSets[idx_tile];
    
    int const idx_rand = rand() % size(tile);
    
    return tile[idx_rand];
}
