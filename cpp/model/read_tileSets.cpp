//
//  read_tileSets.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

vector<vector<int>> Model::read_tileSets() const
{
    ifstream inFile("/Users/michiel/Documents/github/vv_routing/data/1_tileSets");
    
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
            ++curr_tile;
            
            tileSets.push_back(vector<int>());
        }
        
        tileSets[idx_tile - 1].push_back(idx_node);
    }
    
    return tileSets;
}
