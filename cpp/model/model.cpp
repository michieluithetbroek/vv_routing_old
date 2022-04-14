//
//  model.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

Model::Model()
:
  d_edges    (read_edges()),
  d_tileSets (read_tileSets()),
  d_nNodes   (get_nNodes()),
  d_env      (),
  d_model    (d_env),
  d_x        (d_nNodes, vector<GRBVar>(d_nNodes, GRBVar())),
  d_u        (d_nNodes, GRBVar())
{
    try
    {
    createVariables();
    createObjective();
    createConstraints();
    
    // Where should Gurobi write its log output
//    d_env.set("LogFile", "mip1.log");
//    d_env.start();
    
        solve(20);
        
        printSolution();
    }
    catch (GRBException const &e)
    {
        cout << e.getMessage() << endl;
    }
}
