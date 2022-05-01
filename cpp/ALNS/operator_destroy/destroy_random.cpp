//
//  destroy_random.cpp
//  vv_routing
//
// Removes n randomly selected nodes. Returns vector with tiles that are removed
//
//  Created by Michiel uit het Broek on 01/05/2022.
//

#include "./../ALNS.ih"

vector<int> ALNS::destroy_random(vector<int> &route, int const nRemovals)
{
    vector<int> indicesTiles;
    indicesTiles.reserve(nRemovals);
    
    for (int idxRemoval = 0; idxRemoval < nRemovals; ++idxRemoval)
    {
        uniform_int_distribution<int> randomInt (1, (int) size(route) - 2);
        
        int const idxRemoved = randomInt(d_generator);
        
        indicesTiles.push_back(d_tileSets_perNode[route[idxRemoved]]);
        
        route.erase(begin(route) + idxRemoved);
    }
    
    return indicesTiles;
}
