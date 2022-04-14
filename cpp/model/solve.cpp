//
//  solve.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "main.hpp"

void Model::solve(int solvingTime)
{
    double mipGap  = 0.05;
  
  
    d_model.set (GRB_DoubleParam_TimeLimit,     solvingTime);   // g_timeLimit / 10);
    d_model.set (GRB_IntParam_PreCrush,         0);         // User callback

    d_model.set (GRB_IntParam_Threads,          6);         // Number of threads
    d_model.set (GRB_DoubleParam_Heuristics,    1.0);
    d_model.set (GRB_IntParam_MIPFocus,         1);         // 1 = focus on solutions
    d_model.set (GRB_DoubleParam_MIPGap,        mipGap);
    d_model.set (GRB_IntParam_OutputFlag,       1);         // 0 = no terminal output

    d_model.set (GRB_DoubleParam_NodefileStart, 1);      // In GB!
    //  d_model.set (GRB_StringParam_NodefileDir,   g_nodeFileDir);

    //   d_model.set(GRB_IntParam_Method, GRB_METHOD_BARRIER);
      
    //  MyCallbackcompact cb(this);
    //  d_model.setCallback(&cb);
      
    d_model.optimize();
  
//   printRoutes();
}
