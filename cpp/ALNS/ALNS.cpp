//
//  ALNS.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 05/05/2022.
//

#include "heuristic.ih"

double Heuristic::ALNS(vector<int> &route_in)
{
    int constexpr nRep = 500;
    
    double const cost1 = loopCost(route_in);
    
    double currCost = loopCost(route_in);
    
    for (int idx = 0; idx < nRep; ++idx)
    {
        for (int jdx = 1; jdx <= 10; ++jdx)
        {
            auto route_tmp = route_in;
            
            auto tiles = destroy_random(route_tmp, jdx);

            shuffle(begin(tiles), end(tiles), d_generator);
            
            CFI_fixed(route_tmp, tiles);
            
            double const cost = loopCost(route_tmp);
            
            if (cost < currCost)
            {
                currCost = cost;
                route_in = route_tmp;
                
//                cout << setw(4) << idx << setw(4) << jdx << setw(10) << cost << endl;
            }
        }
        
        for (int jdx = 1; jdx <= 10; ++jdx)
        {
            auto route_tmp = route_in;
            
            auto tiles = destroy_random_sequence(route_tmp, jdx);

            shuffle(begin(tiles), end(tiles), d_generator);
            
            CFI_fixed(route_tmp, tiles);
            
            double const cost = loopCost(route_tmp);
            
            if (cost < currCost)
            {
                currCost = cost;
                route_in = route_tmp;
                
//                cout << setw(4) << idx << setw(4) << jdx << " seq" << setw(10) << cost << endl;
            }
        }
    }
    
    double const cost2 = loopCost(route_in);
    
    return cost1 - cost2;
}
