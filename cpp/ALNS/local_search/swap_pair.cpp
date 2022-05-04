//
//  swap_pair.cpp
//  vv_routing
//
// Swap two pairs and allow to reverse their order
//
// We do not allow swapping nodes next to each other. This
// will be done by relocate anyway.
//
//  Created by Michiel uit het Broek on 01/05/2022.
//

#include "./../ALNS.ih"

bool ALNS::swap_pair(vector<int> &route)
{
    auto const start = std::chrono::system_clock::now();
    
    size_t const n = size(route);
    
    double bestSaving = numeric_limits<double>::lowest();
    int bestOption  = -1;
    size_t bestIdxA = -1;
    size_t bestIdxB = -1;
    
    for (size_t idxA = 1; idxA < n - 3; ++idxA)
    {
        for (size_t idxB = idxA + 3; idxB < n - 2; ++idxB)
        {
            int const idx_prevA  = route[idxA - 1];
            int const idx_currA1 = route[idxA];
            int const idx_currA2 = route[idxA + 1];
            int const idx_nextA  = route[idxA + 2];
            
            int const idx_prevB  = route[idxB - 1];
            int const idx_currB1 = route[idxB];
            int const idx_currB2 = route[idxB + 1];
            int const idx_nextB  = route[idxB + 2];
            
            double const costSaving = d_cost[idx_prevA][idx_currA1]
                                    + d_cost[idx_currA2][idx_nextA]
                                    + d_cost[idx_prevB][idx_currB1]
                                    + d_cost[idx_currB2][idx_nextB];
            
            // Option 1: do not reverse order
            
            double const costSaving1 = costSaving
                                     - d_cost[idx_prevA][idx_currB1]
                                     - d_cost[idx_currB2][idx_nextA]
                                     - d_cost[idx_prevB][idx_currA1]
                                     - d_cost[idx_currA2][idx_nextB];
            
            // Option 2: reverse both
            
            double const costSaving2 = costSaving
                                     - d_cost[idx_prevA][idx_currB2]
                                     - d_cost[idx_currB1][idx_nextA]
                                     - d_cost[idx_prevB][idx_currA2]
                                     - d_cost[idx_currA1][idx_nextB]
            
                                     + d_cost[idx_currA1][idx_currA2]
                                     - d_cost[idx_currA2][idx_currA1]
                                     + d_cost[idx_currB1][idx_currB2]
                                     - d_cost[idx_currB2][idx_currB1];
            
            // Option 3: reverse A
            
            double const costSaving3 = costSaving
                                     - d_cost[idx_prevA][idx_currB1]
                                     - d_cost[idx_currB2][idx_nextA]
                                     - d_cost[idx_prevB][idx_currA2]
                                     - d_cost[idx_currA1][idx_nextB]
            
                                     + d_cost[idx_currA1][idx_currA2]
                                     - d_cost[idx_currA2][idx_currA1];
            
            // Option 4: reverse B
            
            double const costSaving4 = costSaving
                                     - d_cost[idx_prevA][idx_currB2]
                                     - d_cost[idx_currB1][idx_nextA]
                                     - d_cost[idx_prevB][idx_currA1]
                                     - d_cost[idx_currA2][idx_nextB]
            
                                     + d_cost[idx_currB1][idx_currB2]
                                     - d_cost[idx_currB2][idx_currB1];
            
            // Store best moves
            
            if (costSaving1 > bestSaving)
            {
                bestSaving = costSaving1;
                bestOption = 1;

                bestIdxA = idxA;
                bestIdxB = idxB;
            }
            
            if (costSaving2 > bestSaving)
            {
                bestSaving = costSaving2;
                bestOption = 2;

                bestIdxA = idxA;
                bestIdxB = idxB;
            }
            
            if (costSaving3 > bestSaving)
            {
                bestSaving = costSaving3;
                bestOption = 3;

                bestIdxA = idxA;
                bestIdxB = idxB;
            }
            
            if (costSaving4 > bestSaving)
            {
                bestSaving = costSaving4;
                bestOption = 4;

                bestIdxA = idxA;
                bestIdxB = idxB;
            }
        }
    }
    
    if (bestSaving <= 0.001)
        return false;
    
    double const cost1 = loopCost(route);
    
    int const nodeA1 = route[bestIdxA];
    int const nodeA2 = route[bestIdxA + 1];
    int const nodeB1 = route[bestIdxB];
    int const nodeB2 = route[bestIdxB + 1];
    
    if (bestOption == 1)
    {
        route[bestIdxA]     = nodeB1;
        route[bestIdxA + 1] = nodeB2;
        route[bestIdxB]     = nodeA1;
        route[bestIdxB + 1] = nodeA2;
    }
    
    else if (bestOption == 2)
    {
        route[bestIdxA]     = nodeB2;
        route[bestIdxA + 1] = nodeB1;
        route[bestIdxB]     = nodeA2;
        route[bestIdxB + 1] = nodeA1;
    }
    
    else if (bestOption == 3)
    {
        route[bestIdxA]     = nodeB1;
        route[bestIdxA + 1] = nodeB2;
        route[bestIdxB]     = nodeA2;
        route[bestIdxB + 1] = nodeA1;
    }
    
    else if (bestOption == 4)
    {
        route[bestIdxA]     = nodeB2;
        route[bestIdxA + 1] = nodeB1;
        route[bestIdxB]     = nodeA1;
        route[bestIdxB + 1] = nodeA2;
    }
    
    else
        throw string("ALNS::swap_pair - unknown option\n");
    
    
    double const cost2 = loopCost(route);
    
//    cout << "Swap pair ---------------------------------------------------------" << endl
//         << "   Saving:  " << bestSaving    << endl
//         << "   diff:    " << cost1 - cost2 << endl
//         << "   Cost:    " << cost2         << endl
//         << "   Option:  " << bestOption    << endl
//         << "   idx A:   " << bestIdxA      << endl
//         << "   idx B:   " << bestIdxB      << endl << endl;
    
    if (abs(cost1 - cost2 - bestSaving) > 0.001)
        throw string("ALNS::swap_pair - incorrect saving\n");
    
    auto const end = std::chrono::system_clock::now();
    
    ++d_count_swap_pair;
    
    d_time_swap_pair += (end - start).count();
    
    return true;
}
