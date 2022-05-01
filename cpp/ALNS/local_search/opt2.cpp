//
//  2opt.cpp
//  vv_routing
//
// Note that 2-opt reverse a part of the route. We do not have
// a symmetric distance matrix and thus we have to loop over the
// reverse part. We first ignore this and only do this for the
// best estimated improvement.
//
//  Created by Michiel uit het Broek on 01/05/2022.
//

#include "./../ALNS.ih"

bool ALNS::opt2()
{
    size_t const n = size(d_route);
    
    double bestSaving = numeric_limits<double>::lowest();
    size_t bestIdxA = -1;
    size_t bestIdxB = -1;
    
    for (size_t idxA = 1; idxA < n - 3; ++idxA)
    {
        for (size_t idxB = idxA + 2; idxB < n - 1; ++idxB)
        {
            int const idx_currA = d_route[idxA];
            int const idx_nextA = d_route[idxA + 1];
            
            int const idx_currB = d_route[idxB];
            int const idx_nextB = d_route[idxB + 1];
            
            double const costSaving = d_cost[idx_currA][idx_nextA]
                                    - d_cost[idx_currA][idx_currB]
                                    + d_cost[idx_currB][idx_nextB]
                                    - d_cost[idx_nextA][idx_nextB];
            
            if (costSaving < bestSaving)
                continue;
            
            bestSaving = costSaving;
            
            bestIdxA = idxA;
            bestIdxB = idxB;
        }
    }
    
    if (bestSaving <= 0.001)
        return false;
    
    double const cost1 = loopCost(d_route);
    
    std::reverse(begin(d_route) + bestIdxA + 1, begin(d_route) + bestIdxB + 1);
    
    double const cost2 = loopCost(d_route);
    double const diff  = cost1 - cost2;
    
    cout << "2-OPT -----------------------------------------------------------" << endl
         << "   Saving:  " << bestSaving    << endl
         << "   diff:    " << diff          << endl
         << "   Cost:    " << cost2         << endl
         << "   idx A:   " << bestIdxA      << endl
         << "   idx B:   " << bestIdxB      << endl << endl;
    
    if (diff < 0)
        cout << "-----------------------------------------------------------" << endl
             << "-----------------------------------------------------------" << endl
             << "-----------------------------------------------------------" << endl;
    
    return true;
}
