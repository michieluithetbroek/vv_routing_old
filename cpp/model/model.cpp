//
//  model.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

Model::Model(Init const init, int runtime)
:
  d_idx_inst (1),
  d_nNodes   (init.nNodes()),
  d_edges    (init.edges()),
  d_tileSets (init.tileSets()),
  
  d_env      (),
  d_model    (d_env),
  d_x        (d_nNodes, vector<GRBVar>(d_nNodes, GRBVar())),
  d_u        (d_nNodes, GRBVar())
{ 
    createVariables();
    createObjective();
    createConstraints();
    
    createConstraints_oneWay();
    
//    createConstraints_MTZ();
       
    setInitialSolution();
    
    solve(runtime);
        
    printSolution();
    exportSolution();
}
