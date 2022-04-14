//
//  createConstraints.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

void Model::createConstraints()
{
    // ---------------------------------
    // --- Flow conservation         ---
    // ---------------------------------
    
    for (int idx = 0; idx < d_nNodes; ++idx)
    {
        GRBLinExpr expr = 0;

        for (int jdx = 0; jdx < d_nNodes; ++jdx)
            expr += d_x[idx][jdx] - d_x[jdx][idx];

      d_model.addConstr(expr, GRB_EQUAL, 0, "Flow conservation");
    }
    
    
    // ---------------------------------
    // --- Visit each tile           ---
    // ---------------------------------
    
    for (vector<int> const &tileSet: d_tileSets)
    {
        GRBLinExpr expr = 0;

        for (int idx_node = 0; idx_node < d_nNodes; ++idx_node)
            if (not inTile(idx_node, tileSet))
                for (int jdx_node: tileSet)
                    expr += d_x[idx_node][jdx_node];

        d_model.addConstr(expr, GRB_GREATER_EQUAL, 1, "visit each tile");
    }
}
