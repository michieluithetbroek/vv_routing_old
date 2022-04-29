//
//  read_tileSets_short.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::read_tileSets_short()
{
    ifstream inFile(d_filePath + "_tileSets");
    
    if (not inFile.is_open())
        throw string("Could not open input file: " + d_filePath + "_tileSets");
    
    // Skip empty line
    
    string line;
    getline(inFile, line);

    vector<vector<int>> tileSets;
    
    
    while (getline(inFile, line))
    {
        if (line.empty())
            continue;
        
        tileSets.push_back(vector<int>());
        
        stringstream ss(line);
        
        int idx_tileSet;
        int idx_node;
        
        ss >> idx_tileSet;
        
        if (idx_tileSet != size(tileSets))
        {
            cout << idx_tileSet << endl
                 << size(tileSets) << endl;
            
            throw string("Init::read_tileSets_short - Incorrect tile index");
        }
        
        while (ss >> idx_node)
        {
            if (idx_node == -1)
                break;
            
            tileSets[idx_tileSet - 1].push_back(idx_node - 1);
        }
        
        tileSets[idx_tileSet - 1].shrink_to_fit();
    }
    
    tileSets.shrink_to_fit();
    
    d_tileSets_perTile = tileSets;
    
    d_nTileSets = static_cast<int>(size(d_tileSets_perTile));
}
