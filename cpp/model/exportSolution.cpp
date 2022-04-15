//
//  exportSolution.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 15/04/2022.
//

#include "model.ih"

void Model::exportSolution() const
{
    string const fileName = "/Users/michiel/Documents/github/vv_routing/output/"
        + to_string(d_idx_inst)
        + "_solution.csv";
    
    ofstream outFile(fileName);
    
    for (int idx = 0; idx < d_nNodes; ++idx)
        for (int jdx = 0; jdx < d_nNodes; ++jdx)
            if (d_x[idx][jdx].get(GRB_DoubleAttr_X) > 0.5)
                outFile << idx << ", " << jdx << "\n";
    
}
