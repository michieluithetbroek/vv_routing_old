//
//  model.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

Model::Model(int idx_inst, int runtime)
:
  d_edges    (read_edges(idx_inst)),
  d_tileSets (read_tileSets(idx_inst)),
  d_idx_inst (idx_inst),
  d_nNodes   (get_nNodes()),
  d_env      (),
  d_model    (d_env),
  d_x        (d_nNodes, vector<GRBVar>(d_nNodes, GRBVar())),
  d_u        (d_nNodes, GRBVar())
{
//    printTileData();
    
    createVariables();
    createObjective();
    createConstraints();
    
    createConstraints_oneWay();
    
    createConstraints_MTZ();
       
    setInitialSolution();
    
    solve(runtime);
        
    printSolution();
    exportSolution();
}
