//
//  relocate.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 29/04/2022.
//

#include "./../ALNS.ih"

bool ALNS::relocate(vector<int> &route)
{
    auto const start = std::chrono::system_clock::now();
    
    size_t const n = size(route);
    
    double bestSaving = numeric_limits<double>::lowest();
    size_t bestIdxOut = -1;
    size_t bestIdxIn  = -1;
    
    for (size_t idx_out = 1; idx_out < n - 1; ++idx_out)
    {
        int const idx_prev = route[idx_out - 1];
        int const idx_curr = route[idx_out];
        int const idx_next = route[idx_out + 1];
        
        double const costSaving = d_cost[idx_prev][idx_curr]
                                + d_cost[idx_curr][idx_next]
                                - d_cost[idx_prev][idx_next];
        
        if (costSaving < bestSaving)
            continue;
        
        // Try to insert after idx_in
        for (size_t idx_in = 0; idx_in < n - 1; ++idx_in)
        {
            int const idx_prev_in = route[idx_in];
            int const idx_next_in = route[idx_in + 1];
            
            if (idx_in + 1 == idx_out or idx_in == idx_out)
                continue;
            
            double const costInsert = d_cost[idx_prev_in][idx_curr]
                                    + d_cost[idx_curr][idx_next_in]
                                    - d_cost[idx_prev_in][idx_next_in];
            
            if (costSaving - costInsert > bestSaving)
            {
                bestSaving = costSaving - costInsert;
                bestIdxOut = idx_out;
                bestIdxIn  = idx_in;
            }
        }
    }
    
    if (bestIdxOut == -1 or bestSaving <= 0.001)
        return false;
    
    double const cost1 = loopCost(route);
    
    int const idxNode = route[bestIdxOut];
    
    if (bestIdxOut < bestIdxIn)
        --bestIdxIn;
    
    route.erase(begin(route) + bestIdxOut);
    route.insert(begin(route) + bestIdxIn + 1, idxNode);
    
    double const cost2 = loopCost(route);
    
    
//    cout << "Relocate" << endl
//         << "   Saving:  " << bestSaving << endl
//         << "   Cost:    " << cost2 << endl
//         << "   Pos out: " << bestIdxOut << endl
//         << "   Post in: " << bestIdxIn << endl << endl;
    
    if (abs(cost1 - cost2 - bestSaving) > 0.001)
        throw string("ALNS::relocate - incorrect saving\n");
    
    auto const end = std::chrono::system_clock::now();
    
    d_time_relocate += (end - start).count();
    
    ++d_count_relocate;
    
    return true;
}
