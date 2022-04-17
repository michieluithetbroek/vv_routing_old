//
//  createConstraints_MTZ.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 15/04/2022.
//

#include "model.ih"

void Model::createConstraints_MTZ()
{
    // ---------------------------------------------------------
    // --- u_i variables                                     ---
    // ---------------------------------------------------------
    
    for (int idx = 0; idx < d_nNodes; ++idx)
    {
      string name("u_" + to_string(idx));
        
      d_u[idx] = d_model.addVar(0, d_nNodes, 0.0, GRB_CONTINUOUS, name.c_str());
    }
    
    
    
    // ---------------------------------------------------------
    // --- MTZ constraints                                   ---
    // ---------------------------------------------------------
    
    vector<int> tileSet = d_tileSets[0];
    
    for (int i = 1; i < d_nNodes; ++i)
    {
        for (int j = 1; j < d_nNodes; ++j)
        {
            if (inTile(j, tileSet))
                continue;
            
            GRBLinExpr expr = (d_u[j] - d_u[i] - 1 + (d_nNodes - 1) * (1 - d_x[i][j]));
            
            d_model.addConstr(expr, GRB_GREATER_EQUAL, 0, "Avoid subtours");
        }
    }
}
