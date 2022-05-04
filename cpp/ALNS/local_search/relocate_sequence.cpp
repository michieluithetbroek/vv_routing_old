//
//  relocate_sequence.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 01/05/2022.
//

#include "./../ALNS.ih"

bool ALNS::relocate_sequence(vector<int> &route)
{
    auto const start = std::chrono::system_clock::now();
    
    size_t const n = size(route);
    size_t const maxSize = 5;
    
    double bestSaving = numeric_limits<double>::lowest();
    size_t bestIdxOut = -1;
    size_t bestIdxIn  = -1;
    size_t bestSize   = -1;
    
    for (size_t idx_size = 1; idx_size < maxSize; ++idx_size)
    {
        for (size_t idx_out = 1; idx_out < n - idx_size - 1; ++idx_out)
        {
            int const idx_prev  = route[idx_out - 1];
            int const idx_curr1 = route[idx_out];
            int const idx_curr2 = route[idx_out + idx_size - 1];
            int const idx_next  = route[idx_out + idx_size];
            
            double const costSaving = d_cost[idx_prev][idx_curr1]
                                    + d_cost[idx_curr2][idx_next]
                                    - d_cost[idx_prev][idx_next];
            
            if (costSaving < bestSaving)
                continue;
            
            // Try to insert after idx_in
            
            for (size_t idx_in = 0; idx_in < n - 1; ++idx_in)
            {
                if (idx_in >= idx_out - 1 and idx_in <= idx_out + idx_size - 1)
                    continue;
                
                int const idx_prev_in = route[idx_in];
                int const idx_next_in = route[idx_in + 1];
                
                double const costInsert = d_cost[idx_prev_in][idx_curr1]
                                        + d_cost[idx_curr2][idx_next_in]
                                        - d_cost[idx_prev_in][idx_next_in];
                
                if (costSaving - costInsert > bestSaving)
                {
                    bestSaving = costSaving - costInsert;
                    bestIdxOut = idx_out;
                    bestIdxIn  = idx_in;
                    bestSize   = idx_size;
                }
            }
        }
    }
    
    if (bestSaving <= 0.001)
        return false;
    
    double const cost1 = loopCost(route);
     
    if (bestIdxOut < bestIdxIn)
        bestIdxIn -= bestSize;
    
    vector<int> const tmpRoute (begin(route) + bestIdxOut,
                                begin(route) + bestIdxOut + bestSize);
    
    route.erase(begin(route) + bestIdxOut, begin(route) + bestIdxOut + bestSize);
    route.insert(begin(route) + bestIdxIn + 1, begin(tmpRoute), end(tmpRoute));
    
    double const cost2 = loopCost(route);
    
//    cout << "---------------------------------------------------------" << endl
//         << "---------------------------------------------------------" << endl
//         << "---------------------------------------------------------" << endl << endl;
//
//    cout << "Relocate sequence" << endl
//         << "   Saving:  " << bestSaving << endl
//         << "   Cost:    " << cost2      << endl
//         << "   Pos out: " << bestIdxOut << endl
//         << "   Post in: " << bestIdxIn  << endl
//         << "   size:    " << bestSize   << endl << endl;
    
    if (abs(cost1 - cost2 - bestSaving) > 0.001)
        throw string("ALNS::relocate_sequence - incorrect saving\n");
    
    ++d_count_relocate_sequence;
    
    auto const end = std::chrono::system_clock::now();
    
    d_time_relocate_sequence += (end - start).count();
    
    return true;
}
