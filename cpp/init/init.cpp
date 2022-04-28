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
    read_edges();
    read_tileSets();

    cout << "Init constructor" << endl;
    
    printTileData();
    
    cout << "Init constructor" << endl;
    
    set_nNodes();
    create_costMatrix();
}
