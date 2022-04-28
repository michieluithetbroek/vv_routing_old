//
//  read_edges.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#include "init.ih"

void Init::read_edges()
{
    ifstream inFile(d_filePath);
    
    if (not inFile.is_open())
        throw string("Could not open input file");
    
    int from;
    int to;
    double dist;
    
    vector<Edge> edges;
    
    while (inFile >> from >> to >> dist)
    {
        edges.emplace_back(Edge{from - 1, to - 1, dist});
    }
    
    edges.shrink_to_fit();
    
    d_edges = edges;
}
