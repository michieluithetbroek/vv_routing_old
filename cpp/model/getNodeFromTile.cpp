//
//  getNodeFromTile.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 23/04/2022.
//

#include "model.ih"

int Model::getNodeFromTile(int idx_tile, std::mt19937_64 &gen) const
{
    auto const &tile = d_tileSets[idx_tile];
    
    std::uniform_int_distribution<int> distribution(0, (int)size(tile) - 1);
    
    
    int const idx_rand = distribution(gen);
    
    return tile[idx_rand];
}
