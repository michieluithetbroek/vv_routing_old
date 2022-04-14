//
//  model.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#pragma once

#include <vector>

class Model
{
    struct Edge
    {
        int from;
        int to;
        double dist;
    };
    
    int d_nNodes;
    
    std::vector<Edge> const d_edges;
    std::vector<std::vector<int>> const d_tileSets;
    
public:
    Model();
    
private:
    std::vector<Edge> read_edges() const;
    std::vector<std::vector<int>> read_tileSets() const;
};
