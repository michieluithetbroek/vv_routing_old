//
//  get_CI_tile.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 03/05/2022.
//

#include "ALNS.ih"

Result ALNS::get_CI_tile (vector<int> const &route, int const idx_tile) const
{
    Result result;
    
    for (int const idx_node: d_tileSets_perTile[idx_tile])
    {
        auto const result_CI = get_CI(route, idx_node);

        if (result_CI.cost < result.cost)
        {
            result.idx_tile = idx_tile;
            result.idx_node = idx_node;
            result.idx_pos  = result_CI.idx_pos;
            result.cost     = result_CI.cost;
        }
    }
    
    return result;
}
