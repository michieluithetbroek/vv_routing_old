//
//  create_tileConnected.cpp
//  vv_routing
//
// A tile set is connected if there is a path shorter
// than x kilometer
//
//  Created by Michiel uit het Broek on 05/05/2022.
//

#include "init.ih"

void Init::create_tileConnected(double const maxDist)
{
    d_tileConnnected = vector(d_nTileSets, vector<bool>(d_nTileSets));
    
    for (int idx_tileA = 0; idx_tileA < d_nTileSets; ++idx_tileA)
        for (int idx_tileB = 0; idx_tileB < d_nTileSets; ++idx_tileB)
            d_tileConnnected[idx_tileA][idx_tileB] = tilesConnected(idx_tileA, idx_tileB, maxDist);
}
