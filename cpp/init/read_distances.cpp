//
//  read_distances.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::read_distances()
{
    ifstream inFile(d_filePath + "_distances");
    
    if (not inFile.is_open())
        throw string("Init::read_distances - Could not open input file");
    
    string line;
    int idx_from = -1;
    
    while (getline(inFile, line))
    {
        if (line.empty())
            continue;

        ++idx_from;
        
        d_cost.push_back(vector<double>());
        
        stringstream ss(line);
        
        double dist;
        
        while (ss >> dist)
            d_cost[idx_from].push_back(dist);
        
        d_cost[idx_from].shrink_to_fit();
    }
    
    d_cost.shrink_to_fit();
    
    int const nRow = (int) size(d_cost);
    
    for (auto const &row: d_cost)
        if (size(row) != nRow)
            throw string("Init::read_distances - Incorrect dimension distance matrix");

    cout << "n = " << nRow << endl;
}
