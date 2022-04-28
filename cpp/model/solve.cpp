//
//  solve.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

void Model::solve(int solvingTime)
{
    double mipGap  = 0.05;
  
    d_model.set (GRB_DoubleParam_TimeLimit,     solvingTime);   // g_timeLimit / 10);
    d_model.set (GRB_IntParam_PreCrush,         0);         // consider 1 when adding user constraints
    d_model.set (GRB_IntParam_LazyConstraints,  1);         // must be 1 if lazy constraints are added

    d_model.set (GRB_IntParam_Threads,          4);         // Number of threads
    d_model.set (GRB_DoubleParam_Heuristics,    0.1);      // weight on finding heuristic solutions (1 = max)
    d_model.set (GRB_IntParam_MIPFocus,         2);         // 1 = focus on solutions, 3 = focus on bound
    d_model.set (GRB_DoubleParam_MIPGap,        mipGap);
    d_model.set (GRB_IntParam_OutputFlag,       1);         // 0 = no terminal output
    
//    d_model.set (GRB_IntParam_Presolve,   2);         // 0-2 https://www.gurobi.com/documentation/9.1/refman/presolve.html
//    d_model.set (GRB_IntParam_Cuts,       1);         // 0-3 https://www.gurobi.com/documentation/9.1/refman/cuts.html

    d_model.set (GRB_DoubleParam_NodefileStart, 8);      // In GB!
    //  d_model.set (GRB_StringParam_NodefileDir,   g_nodeFileDir);

    //   d_model.set(GRB_IntParam_Method, GRB_METHOD_BARRIER);
      
      Mycallback cb(this);
      d_model.setCallback(&cb);
      
    d_model.optimize();
}

// no cuts, no presolve

// cuts = 3, no presolve


// no cuts, presolve = 2


// cuts = 3, presolve = 2
// 94520  92992 4785.01866   29   96 9975.80000 4701.79319  52.9%  14.7  170s
// 98333  96841 4783.16680   27   95 9975.80000 4706.26803  52.8%  14.7  175s
//102716 101085 5039.00333   22   66 9975.80000 4710.65000  52.8%  14.6  180s

// cuts = 2, presolve = 2
//136371 134565 4899.02000   37   51 10289.8000 4713.50000  54.2%   8.9  170s
//141749 139806 4956.44500   38   56 10289.8000 4718.25000  54.1%   8.9  175s
//147477 145615 5128.45000   48   37 10289.8000 4722.29500  54.1%   8.9  180s

// cuts = 1, presolve = 2
//189037 187255 5004.36786   37   51 9465.70000 4729.04286  50.0%   8.6  170s
//194305 192618 4828.25000   32   56 9465.70000 4732.15000  50.0%   8.6  175s
//201030 198964 4772.55000   42   26 9465.70000 4736.35000  50.0%   8.6  180s

// cuts = 0, presolve = 2
//293381 292210 4594.45000   38   26 10262.9000 4500.95000  56.1%   8.9  170s
//302395 300799 4567.30000   37   34 10262.9000 4506.50000  56.1%   9.0  175s
//309974 308738 4731.32500   36   33 10262.9000 4510.36250  56.1%   9.0  180s

// cuts = 3, presolve = 1
//85640 84069 4850.99250   26   70 10092.1000 4736.80815  53.1%  12.9  170s
//90017 88307 5314.33889   36   40 10092.1000 4741.69375  53.0%  12.8  175s
//94258 92448 4787.96875   27   63 10092.1000 4746.38619  53.0%  12.7  180s

// cuts = 2, presolve = 1
//107917 106209 4931.70000   28   40 10541.2000 4723.97072  55.2%  12.1  170s
//111366 109634 5011.51818   34   47 10541.2000 4727.06500  55.2%  12.1  175s
//114905 112988 4830.75000   45   40 10541.2000 4729.91880  55.1%  12.1  180s

// cuts = 1, presolve = 1

