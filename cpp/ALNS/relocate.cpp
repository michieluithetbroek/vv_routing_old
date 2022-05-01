//
//  relocate.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 29/04/2022.
//

#include "ALNS.ih"

void ALNS::relocate()
{
    size_t const n = size(d_route);
    
    double bestSaving = numeric_limits<double>::lowest();
    size_t bestIdxOut = -1;
    size_t bestIdxIn  = -1;
    
    for (size_t idx_out = 1; idx_out < n - 1; ++idx_out)
    {
        int const idx_prev = d_route[idx_out - 1];
        int const idx_curr = d_route[idx_out];
        int const idx_next = d_route[idx_out + 1];
        
        double const costSaving = d_cost[idx_prev][idx_curr]
                                + d_cost[idx_curr][idx_next]
                                - d_cost[idx_prev][idx_next];
        
        if (costSaving < bestSaving)
            continue;
        
        // Try to insert after idx_in
        for (size_t idx_in = 0; idx_in < n - 1; ++idx_in)
        {
            int const idx_prev_in = d_route[idx_in];
            int const idx_next_in = d_route[idx_in + 1];
            
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
    
    for (int v: d_route)
        cout << v << " ";
    cout << endl;
    
    if (bestIdxOut == -1 or bestSaving <= 0)
        cout << "No improvement found" << endl;
    
    cout << setprecision(9) << bestSaving << endl
         << bestIdxOut << endl
         << bestIdxIn << endl;
}
