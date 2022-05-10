//
//  InitOSM.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 05/05/2022.
//

#pragma once

#include <stdio.h>

struct Node
{
    int idx_node;
    int idx_way;
    
    double lon;
    double lat;
    
    int tile_x;
    int tile_y;
    
    // Constructor
    
    Node() = default;
    
    Node(int idx_node, int idx_way,
         double lon, double lat,
         int tile_x, int tile_y)
    :
      idx_node (idx_node),
      idx_way  (idx_way),
      lon      (lon),
      lat      (lat),
      tile_x   (tile_x),
      tile_y   (tile_y)
    { }
    
    bool operator<(Node const &other) const
    {
        return idx_node < other.idx_node;
    };
    
    bool operator==(Node const &other) const
    {
        return idx_node == other.idx_node;
    };
};


class InitOSM
{
    std::vector<Node> d_nodes;
    
public:
    InitOSM();
    
    void makeUnique()
    {
        std::sort(begin(d_nodes), end(d_nodes));
        
        auto ip = std::unique(begin(d_nodes), end(d_nodes));
        
        d_nodes.resize(std::distance(begin(d_nodes), ip));
    }
    
    void reindex()
    {
        for (size_t idx = 0; idx < size(d_nodes); ++idx)
            d_nodes[idx].idx_node = static_cast<int>(idx);
    }
};
