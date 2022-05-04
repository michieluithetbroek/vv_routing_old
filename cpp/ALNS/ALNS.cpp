//
//  ALNS.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "ALNS.ih"

ALNS::ALNS(Init const init)
:
  d_nNodes           (init.nNodes()),
  d_nTiles           (init.nTileSets()),
  d_maxTileSize      (0),
  d_cost             (init.cost()),
  d_tileSets_perTile (init.tileSets()),
  d_tileSets_perNode (init.tileSets_perNode()),
  d_seed             (std::random_device()()),
  d_generator        (1)
{
    auto const start = std::chrono::system_clock::now();
    
    cout << fixed << setprecision(2)
         << "Seed = " << d_seed << endl
         << endl;
    
    reduce_tilesets();
    
    bool const printRoutes = false;
    
//    initial_random (printRoutes);
//    initial_CFI_A  (printRoutes);
//    initial_CFI_B  (printRoutes);
    
    initial_CFI_A2 (printRoutes);

    printRoute();
    
    cout << "\ncost start: " << loopCost(d_route) << "\n\n";
    
    
    double currCost = loopCost(d_route);
    
    for (int idx = 0; idx < 100; ++idx)
    {
        for (int jdx = 1; jdx <= 10; ++jdx)
        {
            auto route = d_route;
            
            auto tiles = destroy_random(route, jdx);

            shuffle(begin(tiles), end(tiles), d_generator);
            
            CFI_fixed(route, tiles);
            
            double const cost = loopCost(route);
            
            if (cost < currCost)
            {
                currCost = cost;
                d_route = route;
                
                cout << setw(4) << idx << setw(4) << jdx << setw(10) << cost << endl;
            }
        }
        
        for (int jdx = 1; jdx <= 10; ++jdx)
        {
            auto route = d_route;
            
            auto tiles = destroy_random_sequence(route, jdx);

            shuffle(begin(tiles), end(tiles), d_generator);
            
            CFI_fixed(route, tiles);
            
            double const cost = loopCost(route);
            
            if (cost < currCost)
            {
                currCost = cost;
                d_route = route;
                
                cout << setw(4) << idx << setw(4) << jdx << " seq" << setw(10) << cost << endl;
            }
        }
    }
    
    auto const end = std::chrono::system_clock::now();
    
    cout << "\nFinal solution\n\n";
    
    printRoute();
    
    cout << "Cost = " << loopCost(d_route) << endl;
    
    cout << "\nTimings\n"
         << "  Replace        " << setw(8)  << d_time_replace_node / 1000000
                                << setw(10) << d_count_replace_node << "\n"
         << "  Relocate       " << setw(8)  << d_time_relocate / 1000000
                                << setw(10) << d_count_relocate << "\n"
         << "  Relocate tile  " << setw(8)  << d_time_relocate_tile / 1000000
                                << setw(10) << d_count_relocate_tile << "\n"
         << "  Relocate tiles " << setw(8)  << d_time_relocate_tiles / 1000000
                                << setw(10) << d_count_relocate_tiles << "\n"
         << "  Relocate seq   " << setw(8)  << d_time_relocate_sequence / 1000000
                                << setw(10) << d_count_relocate_sequence << "\n"
         << "  Swap           " << setw(8)  << d_time_swap / 1000000
                                << setw(10) << d_count_swap << "\n"
         << "  Swap pair      " << setw(8)  << d_time_swap_pair / 1000000
                                << setw(10) << d_count_swap_pair << "\n"
         << "  2-opt          " << setw(8)  << d_time_opt2 / 1000000
                                << setw(10) << d_count_opt2 << "\n\n"
         << "  Loop costs     " << setw(8)  << d_time_loopCost / 1000000 << "\n"
         << "  Total          " << setw(8)  << static_cast<double>((end - start).count()) / 1000000 << endl;
}


