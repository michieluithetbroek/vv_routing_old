//
//  replace_node.cpp
//  vv_routing
//
// Replace node by node in the same tile
//
//  Created by Michiel uit het Broek on 03/05/2022.
//

#include "./../ALNS.ih"

bool ALNS::replace_node (vector<int> &route)
{
    auto const start = std::chrono::system_clock::now();
    
    size_t const n = size(route);
    
    bool improvement = false;
    
    for (size_t idx_out = 1; idx_out < n - 1; ++idx_out)
    {
        double bestSaving = numeric_limits<double>::lowest();
        
        int bestNode = -1;
        
        int const idx_prev = route[idx_out - 1];
        int const idx_curr = route[idx_out];
        int const idx_next = route[idx_out + 1];
        
        double const costSaving = d_cost[idx_prev][idx_curr]
                                + d_cost[idx_curr][idx_next];
        
        int const idx_tile = d_tileSets_perNode[idx_curr];
        
        auto const &tile = d_tileSets_perTile[idx_tile];
        
        for (int const idx_node: tile)
        {
            double const costInsert = d_cost[idx_prev][idx_node]
                                    + d_cost[idx_node][idx_next];

            if (costSaving - costInsert >= bestSaving)
            {
                bestSaving = costSaving - costInsert;
                
                bestNode = idx_node;
            }
        }
        
        if (costSaving < 0)
            throw string("ALNS::replace_node - negative cost saving?");
        
        if (costSaving <= 5)
            continue;
        
        improvement = true;
        
        route[idx_out] = bestNode;
        
        ++d_count_replace_node;
    }
    
    auto const end = std::chrono::system_clock::now();
    
    d_time_replace_node += (end - start).count();
    
    return improvement;
}

