//
//  createConstraints_MTZ.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 15/04/2022.
//

#include "model.ih"

void Model::createConstraints_MTZ()
{
    d_model.addConstr(d_u[0], GRB_EQUAL, 0, "Avoid subtours");

    for (int i = 1; i < d_nNodes; ++i)
    {
        for (int j = 1; j < d_nNodes; ++j)
        {
            GRBLinExpr expr = (d_u[j] - d_u[i] - 1 + (d_nNodes - 1) * (1 - d_x[i][j]));
            
            d_model.addConstr(expr, GRB_GREATER_EQUAL, 0, "Avoid subtours");
        }
    }
}
