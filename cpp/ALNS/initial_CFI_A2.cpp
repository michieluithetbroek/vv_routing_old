//
//  initial_CFI_A2.cpp
//  vv_routing
//
// Select a random starting node. Then insert cheapest insertion
// where we only allow a node from a randomly selected tile
//
//  Created by Michiel uit het Broek on 29/04/2022.
//

#include "ALNS.ih"

void ALNS::initial_CFI_A2(bool const printRoutes)
{
    int const nRep = 1000;
    
    double bestCost = numeric_limits<double>::max();
    vector<int> bestRoute;
    
    random_device dev;
    mt19937 generator (dev());
    
    uniform_int_distribution<int> dis(0, d_nNodes - 1);
    
    for (int idx_rep = 0; idx_rep < nRep; ++idx_rep)
    {
        // ---------------------------------------------------
        // --- Select random start node                    ---
        // ---------------------------------------------------
        
        int const start_node = dis(generator);
        
        vector<int> route({start_node, start_node});
        route.reserve(d_nTiles + 1);
        
        
        
        // ---------------------------------------------------
        // --- Generate random order of remaining tiles    ---
        // ---------------------------------------------------
        
        int const exclude_tile = d_tileSets_perNode[start_node];
        
        vector<int> indices_tiles;
        indices_tiles.reserve(d_nTiles - 1);
        
        for (int idx_tile = 0; idx_tile < d_nTiles; ++idx_tile)
            if (idx_tile != exclude_tile)
                indices_tiles.push_back(idx_tile);

        shuffle(begin(indices_tiles), end(indices_tiles), generator);
        
        
        
        // ---------------------------------------------------
        // --- Find cheapest insertion for each tile       ---
        // ---------------------------------------------------
           
        for (int const idx_tile: indices_tiles)
        {
            double bestInsertCost = numeric_limits<double>::max();
            int bestInsert = -1;
            int bestNode   = -1;
            
            for (int const idx_node: d_tileSets_perTile[idx_tile])
            {
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
        }
        
        
        
        // --------------------------------------------
        // --- Compute costs                        ---
        // --------------------------------------------
        
        size_t const n = size(route);
        
        double cost = d_cost[route[n - 1]][route[0]];
        
        for (int idx = 0; idx < n - 1; ++idx)
        {
            int from = route[idx];
            int to   = route[idx + 1];
            
            cost += d_cost[from][to];
        }
        
        if (cost < bestCost)
        {
            bestCost  = cost;
            bestRoute = route;
            
            cout << "A2 "
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
