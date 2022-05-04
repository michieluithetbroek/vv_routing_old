//
//  localsearch.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 02/05/2022.
//

#include "ALNS.ih"

double ALNS::localsearch(vector<int> &route)
{
    double const cost1 = loopCost(route);
    
    int cnt = 500;
    
    while (replace_node(route) and cnt-- >= 0);
    
    cnt = 1000;
    
    while (relocate(route) and cnt-- >= 0);
    
    cnt = 1000;
    
    bool finished = false;
    
    while (not finished and cnt-- >= 0)
    {
        finished = true;
        
        if (relocate(route))
            finished = false;
        
        if (swap(route))
            finished = false;

        swap_pair(route);

        opt2(route);

        relocate_sequence(route);
        
        if (relocate_tile(route))
            finished = false;
        
        if (relocate_tiles(route))
            finished = false;
    }
    
    double const cost2 = loopCost(route);
    
    return cost1 - cost2;
}
