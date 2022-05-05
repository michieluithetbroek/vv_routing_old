//
//  init.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#pragma once

#include <stdio.h>
#include <vector>
#include <string>

struct Edge
{
    int from;
    int to;
    double dist;
};

class Init
{
    int const d_defaultCost = 99999;
    
    std::vector<Edge> d_edges;
    
    std::vector<std::vector<double>> d_cost;
    
    std::vector<std::vector<int>> d_tileSets_perTile;
    std::vector<int> d_tileSets_perNode;
    
    std::vector<std::vector<bool>> d_tileConnnected;
    
    std::string d_filePath;
    
    int d_nNodes;
    int d_nTileSets;
    
    int d_nTilesX = -1;
    int d_nTilesY = -1;
    
public:
    
    Init(int idx_inst, double maxDist);
    
    // Getters
    
    int nNodes() const;
    int nTileSets() const;
    
    int nTilesX() const;
    int nTilesY() const;
    
    std::vector<Edge> edges() const;
    std::vector<std::vector<int>> tileSets() const;
    std::vector<int> tileSets_perNode() const;
    std::vector<std::vector<bool>> tileConnected() const;
    
    
    std::vector<std::vector<double>> cost() const;
    
    // Print data
    
    void printTileData() const;
    
private:
    void read_edges();
    void read_distances();
    
    void read_tileSets_long();
    void read_tileSets_short();
    
    void set_nNodes();

    void create_tileSet_perNode();
    void create_costMatrix();
    void create_tileConnected(double const maxDist);
    
    bool tilesConnected(int idx_tileA, int idx_tileB, double maxDist) const;
};

inline int Init::nNodes() const
{
    return d_nNodes;
}

inline int Init::nTileSets() const
{
    return d_nTileSets;
}

inline int Init::nTilesX() const
{
    return d_nTilesX;
}

inline int Init::nTilesY() const
{
    return d_nTilesY;
}

inline std::vector<Edge> Init::edges() const
{
    return d_edges;
}

inline std::vector<std::vector<int>> Init::tileSets() const
{
    return d_tileSets_perTile;
}

inline std::vector<int> Init::tileSets_perNode() const
{
    return d_tileSets_perNode;
}

inline std::vector<std::vector<double>> Init::cost() const
{
    return d_cost;
}

inline std::vector<std::vector<bool>> Init::tileConnected() const
{
    return d_tileConnnected;
}

inline bool Init::tilesConnected(int const idx_tileA, int const idx_tileB, double maxDist) const
{
    auto const tileA = d_tileSets_perTile[idx_tileA];
    auto const tileB = d_tileSets_perTile[idx_tileB];
    
    for (int idx_nodeA: tileA)
        for (int idx_nodeB: tileB)
            if (d_cost[idx_nodeA][idx_nodeB] <= maxDist)
                return true;
    
    return false;
}
