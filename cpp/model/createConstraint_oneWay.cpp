//
//  createConstraint_oneWay.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 19/04/2022.
//

#include "model.ih"

void Model::createConstraints_oneWay()
{
    for (vector<int> const &tileSet: d_tileSets)
    {
        for (int idx: tileSet)
        {
            for (int jdx: tileSet)
            {
                GRBLinExpr expr = d_x[idx][jdx] + d_x[jdx][idx];
                d_model.addConstr(expr, GRB_LESS_EQUAL, 1, "One way only");
            }
        }
    }
    
    
    // subtours (n = 3)
    
//    cout << d_nNodes << endl << endl;
//
//    for (int idx = 0; idx < d_nNodes; ++idx)
//    {
//        for (int jdx = 0; jdx < d_nNodes; ++jdx)
//        {
//            if (not edgeExists(idx, jdx))
//                continue;
////
////            for (int kdx = 0; kdx < d_nNodes; ++kdx)
////            {
////                if (not edgeExists(idx, kdx) or not edgeExists(jdx, kdx))
////                    continue;
////
////                GRBLinExpr expr = d_x[idx][jdx] + d_x[jdx][idx];
////                d_model.addConstr(GRBLinExpr{d_x[idx][jdx]
////                    + d_x[idx][kdx]
////                    + d_x[jdx][idx]
////                    + d_x[jdx][kdx]
////                    + d_x[kdx][idx]
////                    + d_x[kdx][jdx]
////                }, GRB_LESS_EQUAL, 2, "Subtours n=2");
////            }
//        }
//    }
        
    
}
