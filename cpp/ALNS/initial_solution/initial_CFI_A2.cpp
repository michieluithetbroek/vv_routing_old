//
//  initial_CFI_A2.cpp
//  vv_routing
//
// Select a random starting node. Then insert cheapest insertion
// where we only allow a node from a randomly selected tile
//
//  Created by Michiel uit het Broek on 29/04/2022.
//

#include "./../heuristic.ih"

void Heuristic::initial_CFI_A2(bool const printRoutes)
{
    int constexpr nRep = 200;
    
    bool constexpr applyALNS = true;
    bool constexpr applyLS2  = true;
    
    cout << "   "
         << setw(6)  << "it"          << " "
         << setw(10) << "Time"        << " "
         << setw(15) << "Length"      << " | "
         << setw(12) << "Saving LS"   << " "
         << setw(12) << "Saving ALNS" << " "
         << setw(12) << "Saving LS"   << "\n";
 
    auto const start = std::chrono::system_clock::now();
    
    double bestCost = numeric_limits<double>::max();
    vector<int> bestRoute;
    
    uniform_int_distribution<int> dis(0, d_nNodes - 1);
    
    for (int idx_rep = 0; idx_rep < nRep; ++idx_rep)
    {
        // ---------------------------------------------------
        // --- Select random start node                    ---
        // ---------------------------------------------------
        
        int const start_node = dis(d_generator);
        
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

        shuffle(begin(indices_tiles), end(indices_tiles), d_generator);
        
        
        
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
//                auto const result = get_CI(route, idx_node);
//                
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
        // --- Improve route                        ---
        // --------------------------------------------
        
        double const saving_LS1  = localsearch(route);
        double const saving_ALNS = (applyALNS ? ALNS(route) : 0);
        double const saving_LS2  = (applyLS2  ? localsearch(route) : 0);
        
        
        
        // --------------------------------------------
        // --- Compute costs                        ---
        // --------------------------------------------
        
        double const cost = loopCost(route);
        
        if (cost < bestCost or idx_rep == nRep - 1)
        {
            if (cost < bestCost)
            {
                bestCost  = cost;
                bestRoute = route;
            }
            
            auto const end = std::chrono::system_clock::now();
            
            auto const duration = end - start;
            
            auto const hrs  = duration_cast<hours>(duration);
            auto const mins = duration_cast<minutes>(duration - hrs);
            auto const secs = duration_cast<seconds>(duration - hrs - mins);
             
            stringstream stime;
            
            stime << fixed
                  << setw(2) << setfill('0') << hrs.count()  << ":"
                  << setw(2) << setfill('0') << mins.count() << "."
                  << setw(2) << setfill('0') << secs.count();
            
            cout << "A2 "
                 << setw(6)  << idx_rep     << " "
                 << setw(10) << stime.str() << " "
                 << setw(12) << (double) ((int) bestCost / 10) / 100  << " km | "
                 << setw(12) << saving_LS1  << " "
                 << setw(12) << saving_ALNS << " "
                 << setw(12) << saving_LS2  << " ";

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
