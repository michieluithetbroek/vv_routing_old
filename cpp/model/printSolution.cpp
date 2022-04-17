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
    // --- Nodes in tileSet 0             ---
    // --------------------------------------
    
    cout << "\nTile set 0: ";
    
    for (int idx: d_tileSets[0])
        cout << idx << " ";
    cout << "\n\n";
    
    
    // --------------------------------------
    // --- Nodes in tileSet 0             ---
    // --------------------------------------
    
    cout << "Traversed arcs:\n";
    
    for (int idx = 0; idx < d_nNodes; ++idx)
        for (int jdx = 0; jdx < d_nNodes; ++jdx)
            if (d_x[idx][jdx].get(GRB_DoubleAttr_X) > 0.5)
                cout << setw(4) << idx << " " << setw(5) << jdx << endl;
    
    cout << endl;
    
    
    
    // --------------------------------------
    // --- Which nodes are visited?       ---
    // --------------------------------------
    
    vector<bool> visitedNodes(d_nNodes, false);
    
    for (int idx = 0; idx < d_nNodes; ++idx)
        for (int jdx = 0; jdx < d_nNodes; ++jdx)
            if (d_x[idx][jdx].get(GRB_DoubleAttr_X) > 0.5)
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
    // --- Print routes                   ---
    // --------------------------------------
    
    // Is a route traversing this node already printed?
    
    vector<bool> routePrinted(d_nNodes, false);
    
    // Our formulation does still allow multiple routes..
    // We therefore consider each node as starting node of a route
    
    for (int start_node = 0; start_node < d_nNodes; ++start_node)
    {
        if (not visitedNodes[start_node])
            continue;
        
        if (routePrinted[start_node])
            continue;
        
        // There is a route that traversing start_node
        // This can be print routes twice because multiple
        // nodes in a tile can be visited by a single route
        
        int curr_node = start_node;
        
        cout << "\n\nRoute:\n";
        
        int cnt = 40;
        do
        {
            cout << curr_node << " ";
            
            routePrinted[curr_node] = true;
            
            int idx = -1;
            while (d_x[curr_node][++idx].get(GRB_DoubleAttr_X) < 0.5);
            
            curr_node = idx;
            --cnt;
            
        } while (curr_node != start_node && cnt >= 0);
    }
    
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
