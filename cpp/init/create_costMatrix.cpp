//
//  create_costMatrix.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::create_costMatrix()
{
    d_cost = vector<vector<double>>(d_nNodes,
                                    vector<double>(d_nNodes,
                                                   d_defaultCost));

    for (Edge const &e: d_edges)
        d_cost[e.from][e.to] = e.dist;
}
