//
//  swap.cpp
//  vv_routing
//
// We do not allow swapping nodes next to each other. This
// will be done by relocate anyway.
//
//  Created by Michiel uit het Broek on 01/05/2022.
//

#include "./../ALNS.ih"

bool ALNS::swap()
{
    size_t const n = size(d_route);
    
    double bestSaving = numeric_limits<double>::lowest();
    size_t bestIdxA = -1;
    size_t bestIdxB = -1;
    
    for (size_t idxA = 1; idxA < n - 3; ++idxA)
    {
        for (size_t idxB = idxA + 2; idxB < n - 1; ++idxB)
        {
            int const idx_prevA = d_route[idxA - 1];
            int const idx_currA = d_route[idxA];
            int const idx_nextA = d_route[idxA + 1];
            
            int const idx_prevB = d_route[idxB - 1];
            int const idx_currB = d_route[idxB];
            int const idx_nextB = d_route[idxB + 1];
            
            double const costSaving = d_cost[idx_prevA][idx_currA]
                                    + d_cost[idx_currA][idx_nextA]
                                    + d_cost[idx_prevB][idx_currB]
                                    + d_cost[idx_currB][idx_nextB]
            
                                    - d_cost[idx_prevA][idx_currB]
                                    - d_cost[idx_currB][idx_nextA]
                                    - d_cost[idx_prevB][idx_currA]
                                    - d_cost[idx_currA][idx_nextB];
            
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
    
    std::swap(d_route[bestIdxA], d_route[bestIdxB]);
    
    double const cost2 = loopCost(d_route);
    
    cout << "Swap" << endl
         << "   Saving:  " << bestSaving << endl
         << "   Cost:    " << cost2 << endl
         << "   idx A:   " << bestIdxA << endl
         << "   idx B:   " << bestIdxB << endl << endl;
    
    if (abs(cost1 - cost2 - bestSaving) > 0.001)
        throw string("ALNS::swap - incorrect saving\n");
    
    return true;
}
