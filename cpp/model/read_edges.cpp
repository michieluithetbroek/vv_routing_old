//
//  read_instance.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

vector<Model::Edge> Model::read_edges(int idx_inst) const
{
    string const fileName = "/Users/michiel/Documents/github/vv_routing/data/"
        + to_string(idx_inst)
        + "_distance";
    
    ifstream inFile(fileName);
    
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
