//
//  createVariables.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

void Model::createVariables()
{
    // ---------------------------------------------------------
    // --- x_ij variables                                    ---
    // ---------------------------------------------------------
 
    // Create dummy variables for non-existing arcs
    // This makes modelling of the constraints much easier
    
    for (int idx = 0; idx < d_nNodes; ++idx)
        for (int jdx = 0; jdx < d_nNodes; ++jdx)
            d_x[idx][jdx] = d_model.addVar(0.0, 0.0, 99999, GRB_BINARY, "dummy variable");

    for (Edge const &e: d_edges)
    {
        string name("x_" + to_string(e.from) + "_" + to_string(e.to));
        
        d_x[e.from][e.to] = d_model.addVar(0.0, 1.0, e.dist, GRB_BINARY, name.c_str());
    }
}
