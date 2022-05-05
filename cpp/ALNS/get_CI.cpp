//
//  get_CI.cpp
//  vv_routing
//
// Returns the cheapest insertion location and cost for
// a given node and route
//
//  Created by Michiel uit het Broek on 03/05/2022.
//

#include "heuristic.ih"

Result Heuristic::get_CI (std::vector<int> const &route_in, int const idx_node) const
{
    Result result;
    
    int const n = (int) size(route_in);
    
    for (int idx = 0; idx < n - 1; ++idx)
    {
        int const idx_prev = route_in[idx];
        int const idx_next = route_in[idx + 1];
        
        double const cost = d_cost[idx_prev][idx_node]
                          + d_cost[idx_node][idx_next]
                          - d_cost[idx_prev][idx_next];
       
        if (cost < result.cost)
        {
            result.cost    = cost;
            result.idx_pos = idx;
        }
    }
    
    return result;
}
