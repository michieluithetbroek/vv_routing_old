//
//  printSolution.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

void Model::printSolution() const
{
    // --------------------------------------
    // --- Which nodes are visited?       ---
    // --------------------------------------
    
    vector<bool> visitedNodes(d_nNodes, false);
    
    for (int idx = 0; idx < d_nNodes; ++idx)
        for (int jdx = 0; jdx < d_nNodes; ++jdx)
            if (d_x[idx][jdx].get(GRB_DoubleAttr_X) > 0)
                visitedNodes[jdx] = true;
    
    
    
    // --------------------------------------
    // --- Print visited nodes            ---
    // --------------------------------------
    
    cout << "\nVisited nodes:\n";
    
    for (int idx = 0; idx < d_nNodes; ++idx)
        if (visitedNodes[idx])
            cout << idx << " ";
    
    cout << "\n\n";
    
    
    
    // --------------------------------------
    // --- Print route                    ---
    // --------------------------------------
    
    int start_node = -1;
    
    while (not visitedNodes[++start_node]);
    
    // There is a route that starts with node start_node
    // Now we follow this route
    
    int curr_node = start_node;
    
    cout << "Route:\n";
    
    do
    {
        cout << curr_node << " ";
        
        int idx = -1;
        while (d_x[curr_node][++idx].get(GRB_DoubleAttr_X) == 0);
        
        curr_node = idx;
        
    } while (curr_node != start_node);
    
    cout << "\n\nDistance: " << round(d_model.get(GRB_DoubleAttr_ObjVal) / 100) / 10 << " km\n" << endl;
    
    
    
    // --------------------------------------
    // --- Visited all tiles?             ---
    // --------------------------------------
    
    for (auto const &tileSet: d_tileSets)
    {
        bool visitedTile = false;
        
        for (int const idx_node: tileSet)
            if (visitedNodes[idx_node])
                visitedTile = true;
        
        if (not visitedTile)
            cout << "\n\nNot every tile is visited!\n\n";
    }
}
