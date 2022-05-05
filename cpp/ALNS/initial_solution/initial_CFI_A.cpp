//
//  initial_CFI.cpp
//  vv_routing
//
// Select a random starting node. Then insert cheapest insertion
// where we only allow nodes from tiles that are not visited yet
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "./../heuristic.ih"

void Heuristic::initial_CFI_A(bool const printRoutes)
{
    int const nRep = 1000;
    
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
        
        route[0] = start_node;
        route[1] = start_node;
        
        tileVisited[d_tileSets_perNode[start_node]] = true;
        
        
        // ---------------------------------------------------
        // --- Find cheapest insertion                     ---
        // ---------------------------------------------------
        
        for (int idx_iter = 0; idx_iter < d_nTiles - 1; ++idx_iter)
        {
            double bestInsertCost = numeric_limits<double>::max();
            int bestInsert = -1;
            int bestNode   = -1;
            
            // Which node to insert
            
            for (int idx_node = 0; idx_node < d_nNodes; ++idx_node)
            {
                if (tileVisited[d_tileSets_perNode[idx_node]])
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
            
            route.insert(begin(route) + bestInsert + 1, bestNode);
            
            tileVisited[d_tileSets_perNode[bestNode]] = true;
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
            
            cout << "A "
                 << setw(5)  << idx_rep << " "
                 << setw(10) << cost << " | ";
            
            if (printRoutes)
                for (int v: route)
                    cout << v << " ";
            cout << endl;
        }
    }
    
    cout << endl;
    
    d_currCost = bestCost;
    d_route    = bestRoute;
}
