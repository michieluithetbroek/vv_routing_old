//
//  destroy_random_sequence.cpp
//  vv_routing
//
// Removes a randomly selected sequence of size n.  Returns a vector
// with tiles that are removed
//
//  Created by Michiel uit het Broek on 01/05/2022.
//

#include "./../heuristic.ih"

vector<int> Heuristic::destroy_random_sequence (vector<int> &route_in, int const nRemovals)
{
    vector<int> indicesTiles;
    indicesTiles.reserve(nRemovals);
    
    uniform_int_distribution<int> randomInt (1, (int) size(route_in) - nRemovals - 1);
        
    int const idxStart = randomInt(d_generator);
    
    for (int idx = 0; idx < nRemovals; ++idx)
    {
        indicesTiles.push_back(d_tileSets_perNode[route_in[idxStart]]);
            
        route_in.erase(begin(route_in) + idxStart);
    }
    
    return indicesTiles;
}
