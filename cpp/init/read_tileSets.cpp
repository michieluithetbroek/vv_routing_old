//
//  read_tileSets.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::read_tileSets()
{
    ifstream inFile(d_filePath + "_tileSets");
    
    if (not inFile.is_open())
        throw string("Could not open input file");
    
    vector<vector<int>> tileSets;
    
    int curr_tile = 0;
    int idx_tile;
    int idx_node;
    
    while (inFile >> idx_tile >> idx_node)
    {
        if (idx_tile > curr_tile)
        {
            if (curr_tile > 0)
                tileSets[curr_tile - 1].shrink_to_fit();
                
            ++curr_tile;
            
            tileSets.push_back(vector<int>());
        }
        
        tileSets[idx_tile - 1].push_back(idx_node - 1);
    }
    
    tileSets.shrink_to_fit();
    
    d_tileSets = tileSets;
}
