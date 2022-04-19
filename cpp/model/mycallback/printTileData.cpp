//
//  printTileData.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 19/04/2022.
//

#include "model.ih"

void Model::printTileData() const
{
    for (int idx = 0; idx < size(d_tileSets); ++idx)
    {
        auto const &tile = d_tileSets[idx];
        
        cout << "Tile " << setw(2) << idx << " - ";
        
        for (int v: tile)
            cout << v << ' ';
        
        cout << endl;
    }
    
    throw;
}
