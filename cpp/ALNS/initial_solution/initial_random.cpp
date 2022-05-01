//
//  initial_random.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "./../ALNS.ih"

void ALNS::initial_random(bool const printRoutes)
{
    int const nRep1 = 10;
    int const nRep2 = 25;
    
    double bestCost = numeric_limits<double>::max();
    vector<int> bestRoute;
    
    vector<int> route(d_nTiles, -1);
    
    for (int idxRep1 = 0; idxRep1 < nRep1; ++idxRep1)
    {
        
        // --------------------------------------------
        // --- Random order of tiles                ---
        // --------------------------------------------
        
        vector<int> idx_tiles(d_nTiles, -1);
        
        for (int idx = 0; idx < d_nTiles; ++idx)
            idx_tiles[idx] = idx;
        
        shuffle (begin(idx_tiles), end(idx_tiles), d_generator);
        
        
        
        // --------------------------------------------
        // --- Random node per tile                 ---
        // --------------------------------------------
        
        int bonusReps = 0;
        
        for (int idxRep2 = 0; idxRep2 < nRep2 + bonusReps; ++idxRep2)
        {
            for (int idx = 0; idx < d_nTiles; ++idx)
            {
                int const idx_tile  = idx_tiles[idx];
                auto const &tileSet = d_tileSets_perTile[idx_tile];
                
                uniform_int_distribution<int> dis(0, (int) size(tileSet) - 1);
                
                route[idx] = tileSet[dis(d_generator)];
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
                
                cout << setw(11) << idxRep1 << " "
                     << setw(5)  << idxRep2 << " "
                     << setw(10) << cost << " | ";
                
                if (printRoutes)
                    for (int v: route)
                        cout << v << " ";
                cout << endl;
                
                if (idxRep1 > 10)
                    bonusReps = bonusReps + 2500;
            }
        }
    }
    
    cout << endl;
    
    d_currCost = bestCost;
    d_route    = bestRoute;
}
