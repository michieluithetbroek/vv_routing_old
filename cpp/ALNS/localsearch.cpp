//
//  localsearch.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 02/05/2022.
//

#include "ALNS.ih"

double ALNS::localsearch(vector<int> &route)
{
    bool finished = false;
    
    double const cost1 = loopCost(route);
    
    int cnt = 2500;
    
    while (not finished and cnt-- >= 0)
    {
        finished = true;
        
        if (relocate(route))
            finished = false;

        if (swap(route))
            finished = false;

//        if (swap_pair(route))
//            finished = false;

        if (opt2(route))
            finished = false;

        if (relocate_sequence(route))
            finished = false;
        
        if (relocate_tile(route))
            finished = false;
    }
    
    double const cost2 = loopCost(route);
    
    return cost1 - cost2;
}
