//
//  reduce_tilesets.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 04/05/2022.
//

#include "ALNS.ih"

void ALNS::reduce_tilesets()
{
    if (d_maxTileSize <= 0)
        return;
    
    for (auto &tileSet: d_tileSets_perTile)
    {
        shuffle(begin(tileSet), end(tileSet), d_generator);
        
        if (size(tileSet) > d_maxTileSize)
          tileSet.resize(d_maxTileSize);
        
        sort(begin(tileSet), end(tileSet));
    }
}
