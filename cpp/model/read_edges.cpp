//
//  read_instance.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

vector<Model::Edge> Model::read_edges() const
{
    ifstream inFile("/Users/michiel/Documents/github/vv_routing/data/1_distance");
    
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
    
    return edges;
}
