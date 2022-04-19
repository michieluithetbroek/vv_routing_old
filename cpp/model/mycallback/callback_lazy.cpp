//
//  callback_lazy.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/04/2022.
//

#include "mycallback.ih"

void Mycallback::callback_lazy()
{
    int const nNodes = d_model->d_nNodes;
    
    // --------------------------------------
    // --- Read x values                  ---
    // --------------------------------------
    
    vector<vector<double>> x(nNodes, vector<double>(nNodes));
    
    for (int idx = 0; idx < nNodes; ++idx)
        for (int jdx = 0; jdx < nNodes; ++jdx)
            x[idx][jdx] = getSolution(d_model->d_x[idx][jdx]);

    
    
    // --------------------------------------
    // --- Which nodes are visited?       ---
    // --------------------------------------
    
    vector<bool> visitedNodes(nNodes, false);
    
    for (int idx = 0; idx < nNodes; ++idx)
    {
        for (int jdx = 0; jdx < nNodes; ++jdx)
        {
            if (x[idx][jdx] < 0.1)
                continue;
            
            visitedNodes[jdx] = true;
               
            break;
        }
    }
    
    // How many nodes are visited?
    
    int nNodes_visited = 0;
    
    for (int idx = 0; idx < nNodes; ++idx)
        nNodes_visited += visitedNodes[idx];
    
    
    
    // -----------------------------------
    // --- Find all subtours           ---
    // -----------------------------------
    
    vector<bool> nodeChecked(nNodes, false);
    
    vector<vector<int>> tours;
    
    for (int start_node = 0; start_node < nNodes; ++start_node)
    {
        if (not visitedNodes[start_node])
            continue;
        
        if (nodeChecked[start_node])
            continue;
        
        // Following tour starting at start_node
        
        tours.emplace_back();
        vector<int> &currTour = tours[size(tours) - 1];
        
        int curr_node = start_node;
        int maxTourSize = 1000;
        
        do
        {
            nodeChecked[curr_node] = true;
            
            currTour.push_back(curr_node);
            
            curr_node = d_model->nextNode(x, curr_node);

            --maxTourSize;
            
        } while (curr_node != start_node && maxTourSize >= 0);
    }
    
    
    
    // --------------------------------------
    // --- Add constraints                ---
    // --------------------------------------
    
    if (size(tours) == 1)
        return;
    
    if (size(tours) == 0)
        throw string("No tours found");
    
    
    for (auto const &tour: tours)
    {
        GRBLinExpr expr = 0;
     
        for (int idx: tour)
            for (int jdx: tour)
                expr += d_model->d_x[idx][jdx];
        
        addLazy(expr <= size(tour) - 1);
    }    
}
