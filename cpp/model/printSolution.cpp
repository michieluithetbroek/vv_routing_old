//
//  printSolution.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

void Model::printSolution() const
{
    for (int idx = 0; idx < d_nNodes; ++idx)
        for (int jdx = 0; jdx < d_nNodes; ++jdx)
            if (d_x[idx][jdx].get(GRB_DoubleAttr_X) > 0)
                cout << idx << " " << jdx << endl;
}
