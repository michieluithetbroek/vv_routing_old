//
//  relocate_tiles.cpp
//  vv_routing
//
// Same as relocate_tile but then tile by tile instead
// of overall best improvement
//
//  Created by Michiel uit het Broek on 03/05/2022.
//

#include "./../ALNS.ih"

bool ALNS::relocate_tiles (vector<int> &route)
{
    auto const start = std::chrono::system_clock::now();
    
    size_t const n = size(route);
    
    bool improvement = false;
    
    for (size_t idx_out = 1; idx_out < n - 1; ++idx_out)
    {
        double bestSaving = numeric_limits<double>::lowest();
        
        size_t bestIdxPos_out = -1;
        size_t bestIdxPos_in  = -1;
        int bestIdxNode_out   = -1;
        int bestIdxNode_in    = -1;
        
        int const idx_prev = route[idx_out - 1];
        int const idx_curr = route[idx_out];
        int const idx_next = route[idx_out + 1];
        
        double const costSaving = d_cost[idx_prev][idx_curr]
                                + d_cost[idx_curr][idx_next]
                                - d_cost[idx_prev][idx_next];
        
        if (costSaving < bestSaving)
            continue;
        
        auto tmp_route = route;
        
        tmp_route.erase(begin(tmp_route) + idx_out);
        
        int const idx_tile = d_tileSets_perNode[idx_curr];
        
        for (int const idx_node: d_tileSets_perTile[idx_tile])
        {
            for (size_t idx_in = 0; idx_in < size(tmp_route) - 1; ++idx_in)
            {
                int const idx_prev_in = tmp_route[idx_in];
                int const idx_next_in = tmp_route[idx_in + 1];

                double const costInsert = d_cost[idx_prev_in][idx_node]
                                        + d_cost[idx_node][idx_next_in]
                                        - d_cost[idx_prev_in][idx_next_in];

                if (costSaving - costInsert >= bestSaving)
                {
                    bestSaving = costSaving - costInsert;
                    
                    bestIdxNode_out = idx_curr;
                    bestIdxNode_in  = idx_node;
                    bestIdxPos_in   = idx_in;
                    bestIdxPos_out  = idx_out;
                }
            }
        }
        
        if (bestSaving <= 0.01)
            continue;

        improvement = true;
        
        ++d_count_relocate_tiles;
        
        double const costOld = loopCost(route);
        
        route.erase(begin(route) + bestIdxPos_out);
        route.insert(begin(route) + bestIdxPos_in + 1, bestIdxNode_in);
        
        double const costNew = loopCost(route);
        
    //    cout << "Relocate tile" << endl
    //         << "   saving:     " << bestSaving      << endl
    //         << "   Cost:       " << costNew         << endl
    //         << "   Node out:   " << bestIdxNode_out << endl
    //         << "   Node in:    " << bestIdxNode_in  << endl
    //         << "   Pos out:    " << bestIdxPos_out  << endl
    //         << "   Pos in:     " << bestIdxPos_in   << endl << endl;
        
        if (abs(costOld - costNew - bestSaving) > 0.001)
            throw string("ALNS::relocate_tile - incorrect saving\n");
    }
    
    auto const end = std::chrono::system_clock::now();
    
    d_time_relocate_tiles += (end - start).count();
    
    return improvement;
}
