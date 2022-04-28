//
//  printTileData.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::printTileData() const
{
    for (int idx = 0; idx < size(d_tileSets); ++idx)
    {
        auto const &tile = d_tileSets[idx];
        
        cout << "Tile " << setw(2) << idx << " - ";
        
        for (int v: tile)
            cout << v << ' ';
        
        cout << endl;
    }
}
