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
  d_cost             (init.cost()),
  d_tileSets_perTile (init.tileSets()),
  d_tileSets_perNode (init.tileSets_perNode()),
  d_generator        (std::random_device()())
{
    cout << fixed << setprecision(2);
    
    bool const printRoutes = false;
    
//    initial_random(printRoutes);

//    initial_CFI_A  (printRoutes);
    initial_CFI_A2 (printRoutes);
//    initial_CFI_B  (printRoutes);
    
    bool finished = false;
    
    while (not finished)
    {
        finished = true;
        
        if (relocate())
            finished = false;
        
        if (swap())
            finished = false;
        
        if (swap_pair())
            finished = false;
        
        if (opt2())
            finished = false;
        
        if (relocate_tile())
            finished = false;
    }
    
    cout << "Final solution\n\n";
    
    printRoute();
}
