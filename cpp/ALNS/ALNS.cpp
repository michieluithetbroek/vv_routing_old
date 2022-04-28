//
//  ALNS.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//


#include "ALNS.ih"

ALNS::ALNS(Init const init)
:
  d_nNodes           (init.nNodes()),
  d_nTiles           (init.nTileSets()),
  d_cost             (init.cost()),
  d_tileSets_perTile (init.tileSets()),
  d_tileSets_perNode (init.tileSets_perNode())
{

}
