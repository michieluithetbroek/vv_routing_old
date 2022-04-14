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
    d_model.set (GRB_DoubleParam_Heuristics,    0.05);      // weight on finding heuristic solutions (1 = max)
    d_model.set (GRB_IntParam_MIPFocus,         3);         // 1 = focus on solutions, 3 = focus on bound
    d_model.set (GRB_DoubleParam_MIPGap,        mipGap);
    d_model.set (GRB_IntParam_OutputFlag,       1);         // 0 = no terminal output

    d_model.set (GRB_DoubleParam_NodefileStart, 1);      // In GB!
    //  d_model.set (GRB_StringParam_NodefileDir,   g_nodeFileDir);

    //   d_model.set(GRB_IntParam_Method, GRB_METHOD_BARRIER);
      
    //  MyCallbackcompact cb(this);
    //  d_model.setCallback(&cb);
      
    d_model.optimize();
}
//212935 120554 11686.4600   44    4 13858.6000 10082.8000  27.2%  12.0  100s
// 118518 110818 10241.1767   31   11 13858.6000 10237.8117  26.1%  18.2  100s
//627862 376404 11282.5083   47    5 13858.6000 10265.3667  25.9%  10.8  100s
