//
//  init.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

Init::Init(int idx_inst)
:
  d_filePath ("/Users/michiel/Documents/github/vv_routing/data/"
              + to_string(idx_inst))
{
//    read_edges();
//    read_tileSets_long()
//    create_costMatrix();
    
    read_distances();
    read_tileSets_short();
//    create_edges();
    
    set_nNodes();
    
    create_tileSet_perNode();
    
//    printTileData();
}
