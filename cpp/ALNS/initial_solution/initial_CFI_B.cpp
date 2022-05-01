//
//  initial_CFI_B.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "./../ALNS.ih"

void ALNS::initial_CFI_B(bool const printRoutes)
{
    int const nRep    = 200;
    int const maxIter = 100;
    
    double bestCost = numeric_limits<double>::max();
    vector<int> bestRoute;
    
    uniform_int_distribution<int> dis(0, d_nNodes - 1);
    
    for (int idx_rep = 0; idx_rep < nRep; ++idx_rep)
    { 
        // ---------------------------------------------------
        // --- Select random start node                    ---
        // ---------------------------------------------------
        
        int const start_node = dis(d_generator);
        
        vector<int> route(2, -1);
        
        vector<bool> tileVisited(d_nTiles, false);
        vector<bool> nodeVisited(d_nNodes, false);
        
        route[0] = start_node;
        route[1] = start_node;
        
        nodeVisited[start_node] = true;
        
        
        // ---------------------------------------------------
        // --- Find cheapest insertion                     ---
        // ---------------------------------------------------
        
        for (int idx_iter = 0; idx_iter < maxIter; ++idx_iter)
        {
            double bestInsertCost = numeric_limits<double>::max();
            int bestInsert = -1;
            int bestNode   = -1;
            
            // Which node to insert
            
            for (int idx_node = 0; idx_node < d_nNodes; ++idx_node)
            {
                if (nodeVisited[idx_node])
                    continue;
                
                // Where to insert
            
                for (int idx_insert = 0; idx_insert < size(route) - 1; ++idx_insert)
                {
                    int const idx_from = route[idx_insert];
                    int const idx_to   = route[idx_insert + 1];

                    double const cost = d_cost[idx_from][idx_node]
                                        + d_cost[idx_node][idx_to]
                                        - d_cost[idx_from][idx_to];
                    
                    if (cost < bestInsertCost)
                    {
                        bestInsertCost = cost;
                        bestInsert     = idx_insert;
                        bestNode       = idx_node;
                    }
                }
            }
            
            // Insert node
            
            route.insert(begin(route) + bestInsert + 1, bestNode);
            
            nodeVisited[bestNode] = true;
            tileVisited[d_tileSets_perNode[bestNode]] = true;
            
            // Is every tile visited?
            
            bool finished = true;
            
            for (bool const visited: tileVisited)
                if (not visited)
                    finished = false;
            
            if (finished)
                break;
        }
        
        
        
        // --------------------------------------------
        // --- Remove most expensive nodes          ---
        // --------------------------------------------
        
        if (true)
        {
            vector<int> tileCount(d_nTiles, 0);
            
            for (int const idx_node: route)
                ++tileCount[d_tileSets_perNode[idx_node]];
            
            --tileCount[d_tileSets_perNode[route[0]]];
            
            int const nRemovals = max(0, (int) size(route) - d_nTiles - 1);
            
            for (int idx_removal = 0; idx_removal < nRemovals; ++idx_removal)
            {
                double bestSaving = numeric_limits<double>::lowest();
                int bestNode = -1;
                int bestPos  = -1;

                // Never remove first and last node (the randomly selected start node)

                for (int idx_pos = 1; idx_pos < (int) size(route) - 1; ++idx_pos)
                {
                    int const idx_prev = route[idx_pos - 1];
                    int const idx_node = route[idx_pos];
                    int const idx_next = route[idx_pos + 1];

                    if (tileCount[d_tileSets_perNode[idx_node]] == 1)
                        continue;

                    double const costSaving = d_cost[idx_prev][idx_node]
                                              + d_cost[idx_node][idx_next]
                                              - d_cost[idx_prev][idx_next];

                    if (costSaving >= bestSaving)
                    {
                        bestSaving = costSaving;
                        bestNode   = idx_node;
                        bestPos    = idx_pos;
                    }
                }
                    
                // Remove best removal

                route.erase(begin(route) + bestPos);
                --tileCount[d_tileSets_perNode[bestNode]];
            }
        }
        
        
        // --------------------------------------------
        // --- Improve route                        ---
        // --------------------------------------------
        
        localsearch(route);
        
        
        // --------------------------------------------
        // --- Compute costs                        ---
        // --------------------------------------------
        
        double const cost = loopCost(route);
        
        if (cost < bestCost)
        {
            bestCost  = cost;
            bestRoute = route;
            
            cout << "B " << setw(5) << idx_rep << " "
                 << setw(10) << cost << " | ";
            
            if (printRoutes)
                for (int v: route)
                    cout << v << " ";
            cout << endl;
        }
    }
    
    d_currCost = bestCost;
    d_route    = bestRoute;
}
