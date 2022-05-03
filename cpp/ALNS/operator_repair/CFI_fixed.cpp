//
//  CFI_fixed.cpp
//  vv_routing
//
// Insert nodes one by one using cheapest insertion in given order
// Returns total cost of insertion
//
//  Created by Michiel uit het Broek on 03/05/2022.
//

#include "./../ALNS.ih"

double ALNS::CFI_fixed (vector<int> &route, vector<int> const &tiles)
{
    double cost = 0;
    
    for (int idx_tile: tiles)
    {
        auto const result = get_CI_tile(route, idx_tile);
        
        cost += result.cost;
        
        route.insert(begin(route) + result.idx_pos + 1, result.idx_node);
    }
    
    return cost;
}
