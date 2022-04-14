//
//  createConstraints_MTZ.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 15/04/2022.
//

#include "model.ih"

void Model::createConstraints_MTZ()
{
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

//341080 322456 10602.0875   45    6 13858.6000 10502.2200  24.2%  15.5  100s
