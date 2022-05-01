//
//  relocate_tile.cpp
//  vv_routing
//
// Removes a node and uses CFI to replace this by any node of
// the same tile.
//
//  Created by Michiel uit het Broek on 29/04/2022.
//

//
//  relocate.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 29/04/2022.
//

#include "./../ALNS.ih"

bool ALNS::relocate_tile()
{
    size_t const n = size(d_route);
    
    double bestSaving = numeric_limits<double>::lowest();
    size_t bestIdxPos_out = -1;
    size_t bestIdxPos_in  = -1;
    int bestIdxNode_out   = -1;
    int bestIdxNode_in    = -1;
    
    vector<int> bestRoute;
    
    for (size_t idx_out = 1; idx_out < n - 1; ++idx_out)
    {
        int const idx_prev = d_route[idx_out - 1];
        int const idx_curr = d_route[idx_out];
        int const idx_next = d_route[idx_out + 1];
        
        double const costSaving = d_cost[idx_prev][idx_curr]
                                + d_cost[idx_curr][idx_next]
                                - d_cost[idx_prev][idx_next];
        
        if (costSaving < bestSaving)
            continue;
        
        auto tmp_route = d_route;
        
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
    }

    if (bestSaving <= 0.01)
        return false;

    double const costOld = loopCost(d_route);
    
    d_route.erase(begin(d_route) + bestIdxPos_out);
    d_route.insert(begin(d_route) + bestIdxPos_in + 1, bestIdxNode_in);
    
    double const costNew = loopCost(d_route);
    
    cout << "Relocate tile" << endl
         << "   saving:     " << bestSaving      << endl
         << "   Cost:       " << costNew         << endl
         << "   Node out:   " << bestIdxNode_out << endl
         << "   Node in:    " << bestIdxNode_in  << endl
         << "   Pos out:    " << bestIdxPos_out  << endl
         << "   Pos in:     " << bestIdxPos_in   << endl << endl;
    
    if (abs(costOld - costNew - bestSaving) > 0.001)
        throw string("ALNS::relocate_tile - incorrect saving\n");
    
    return true;
}
