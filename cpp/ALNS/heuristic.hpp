//
//  heuristic.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 28/04/2022.
//

#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <random>
#include <utility>
#include <ostream>

#include "init.hpp"

struct Result
{
    int idx_tile = -1;
    int idx_node = -1;
    int idx_pos  = -2;
    
    double cost = std::numeric_limits<double>::max();
    
    friend std::ostream &operator << (std::ostream &out, Result const &result)
    {
        out << "  tile:  " << result.idx_tile << std::endl
            << "  node:  " << result.idx_node << std::endl
            << "  pos:   " << result.idx_pos  << std::endl
            << "  costs: " << result.cost     << std::endl;
        
        return out;
    }
};

class Heuristic
{
    // Input data
    
    int const d_nNodes;
    int const d_nTiles;
    int const d_maxTileSize;
    
    std::vector<std::vector<double>> const d_cost;
    
    std::vector<std::vector<int>>        d_tileSets_perTile;
    std::vector<int>               const d_tileSets_perNode;
    std::vector<std::vector<bool>> const d_tilesConnected;
    
    // Solution
    
    double d_currCost;
    std::vector<int> d_route;
    
    // Random generator
    
    int const d_seed;
    std::mt19937 d_generator;
    
    // Internal timers
    
    double d_time_replace_node      = 0;
    double d_time_relocate          = 0;
    double d_time_relocate_tile     = 0;
    double d_time_relocate_tiles    = 0;
    double d_time_relocate_sequence = 0;
    double d_time_swap              = 0;
    double d_time_swap_pair         = 0;
    double d_time_opt2              = 0;
    double d_time_loopCost          = 0;
    
    int d_count_replace_node      = 0;
    int d_count_relocate          = 0;
    int d_count_relocate_tile     = 0;
    int d_count_relocate_tiles    = 0;
    int d_count_relocate_sequence = 0;
    int d_count_swap              = 0;
    int d_count_swap_pair         = 0;
    int d_count_opt2              = 0;
    
    int cnt9 = 0;
    
    
public:
    Heuristic(Init const init);
    
    double localsearch (std::vector<int> &route);
    double ALNS        (std::vector<int> &route);
private:
    
    // Other functions
    
    void reduce_tilesets();
    
    // Initial solutions
    
    void initial_random (bool const printRoutes);
    void initial_CFI_A  (bool const printRoutes);
    void initial_CFI_A2 (bool const printRoutes);
    void initial_CFI_B  (bool const printRoutes);
    
    // Local search moves
    
    bool relocate          (std::vector<int> &route);
    bool relocate_tile     (std::vector<int> &route);
    bool relocate_tiles    (std::vector<int> &route);
    bool relocate_sequence (std::vector<int> &route);
    bool swap              (std::vector<int> &route);
    bool swap_pair         (std::vector<int> &route);
    bool opt2              (std::vector<int> &route);
    bool replace_node      (std::vector<int> &route);
    
    // Destroy operators
    
    std::vector<int> destroy_random          (std::vector<int> &route, int const nRemovals);
    std::vector<int> destroy_random_sequence (std::vector<int> &route, int const nRemovals);
    std::vector<int> destroy_random_square   (std::vector<int> &route, int const nRemovals);
    
    // Repair operators
    
    double CFI_fixed (std::vector<int> &route, std::vector<int> const &nodes);
    
    // Helper function
    
    double loopCost(std::vector<int> const &route);
    void printRoute() const;
    
    Result get_CI      (std::vector<int> const &route, int const idx_node) const;
    Result get_CI_tile (std::vector<int> const &route, int const idx_node) const;
};

inline void Heuristic::printRoute() const
{
    for (int v: d_route)
        std::cout << v << " ";
    
    std::cout << '\n';
}

inline double Heuristic::loopCost(std::vector<int> const &route)
{
    auto start = std::chrono::system_clock::now();
    
    size_t const n = size(route);
    
    double cost = d_cost[route[n - 1]][route[0]];
    
    for (int idx = 0; idx < n - 1; ++idx)
    {
        int from = route[idx];
        int to   = route[idx + 1];
        
        cost += d_cost[from][to];
    }
    
    auto end = std::chrono::system_clock::now();
    
    d_time_loopCost += (end - start).count();
    
    return cost;
}
