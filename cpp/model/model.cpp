//
//  model.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

Model::Model()
:
  d_edges    (read_edges()),
  d_tileSets (read_tileSets())
{

}
