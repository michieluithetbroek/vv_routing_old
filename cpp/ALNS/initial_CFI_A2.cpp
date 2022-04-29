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
    int const nRep = 1000000;
    
    double bestCost = numeric_limits<double>::max();
    
    random_device dev;
    mt19937 generator (dev());
    
    for (int idx_rep = 0; idx_rep < nRep; ++idx_rep)
    {
        
        // ---------------------------------------------------
        // --- Select random start node                    ---
        // ---------------------------------------------------
        
        uniform_int_distribution<int> dis(0, d_nNodes - 1);
        
        int const start_node = dis(generator);
        
        vector<int> route(2, -1);
        vector<bool> tileVisited(d_nTiles, false);
        
        route[0] = start_node;
        route[1] = start_node;
        
        tileVisited[d_tileSets_perNode[start_node]] = true;
        
        
        
        // ---------------------------------------------------
        // --- Generate random order of remaining tiles    ---
        // ---------------------------------------------------
        
        vector<int> indices_tiles;
        indices_tiles.reserve(d_nTiles - 1);
        
        int const exclude_tile = d_tileSets_perNode[start_node];
        
        for (int idx_tile = 0; idx_tile < d_nTiles; ++idx_tile)
            if (idx_tile != exclude_tile)
                indices_tiles.push_back(idx_tile);
        
        shuffle(begin(indices_tiles), end(indices_tiles), generator);
        
        
        
        // ---------------------------------------------------
        // --- Find cheapest insertion                     ---
        // ---------------------------------------------------
        
        
        
        for (int idx_iter = 0; idx_iter < d_nTiles - 1; ++idx_iter)
        {
            double bestInsertCost = numeric_limits<double>::max();
            int bestInsert = -1;
            int bestNode   = -1;
            
            
            
            // Which node to insert
            
            auto const &tileSet = d_tileSets_perTile[indices_tiles[idx_iter]];
            
            for (int const idx_node: tileSet)
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
            bestCost = cost;
            
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
}
