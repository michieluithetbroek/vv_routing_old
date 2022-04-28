//
//  ALNS.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//


#include "ALNS.ih"

ALNS::ALNS(Init const init)
:
  d_nNodes    (init.nNodes()),
  d_nTiles    (init.nTileSets()),
  d_cost      (init.cost()),
  d_tileSets  (init.tileSets())
{
    for (auto &v: d_cost)
    {
        for (auto v2: v)
            cout << setw(5) << v2 << " ";
        cout << endl;
    }
}
