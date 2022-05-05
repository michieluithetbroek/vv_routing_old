//
//  CFI_fixed.cpp
//  vv_routing
//
// Insert nodes one by one using cheapest insertion in given order
// Returns total cost of insertion
//
//  Created by Michiel uit het Broek on 03/05/2022.
//

#include "./../heuristic.ih"

double Heuristic::CFI_fixed (vector<int> &route_in, vector<int> const &tiles)
{
    double cost = 0;
    
    for (int idx_tile: tiles)
    {
        auto const result = get_CI_tile(route_in, idx_tile);
        
        cost += result.cost;
        
        route_in.insert(begin(route_in) + result.idx_pos + 1,
                        result.idx_node);
    }
    
    return cost;
}
