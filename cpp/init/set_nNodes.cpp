//
//  set_nNodes.cpp
//  vv_routing
//
//  Loop over edges to find the number of nodes
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::set_nNodes()
{
    int maxVal = 0;
    
    for (Edge const &e: d_edges)
        maxVal = max(maxVal, max(e.from, e.to));
        
    d_nNodes = maxVal + 1;
}
