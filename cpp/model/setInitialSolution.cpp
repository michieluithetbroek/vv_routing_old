//
//  setInitialSolution.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 19/04/2022.
//
//
// A) start at (0, 0), up-down to right, back to from right to left at the bottom
// B) start at (0, 0), up-down to right, back to from right to left at the top
// C) start at (0, 0), right-left to top, back to from top to bottom at the left side
// D) start at (0, 0), right-left to top, back to from right to left at the right side

#include "model.ih"

void Model::setInitialSolution()
{
    srand ((unsigned int)time(NULL));
    
    cout << "\nSet initial solution\n" << endl;

    int const nRep = 1000;
    bool const reversePaths = true;
    
    

    // ---------------------------------
    // --- Create initial tile paths ---
    // ---------------------------------

        vector<vector<int>> paths({{0,1,2,5,4,7,8,7,6,3,0},   // up-down to right, back: right > bottom
                                   {0,1,4,3,6,7,8,5,2,1,0},   // up-down to right, back: top > left
                                   {0,3,6,7,4,5,8,5,2,1,0},   // right-left to top, back: top > left
                                   {0,3,4,1,2,5,8,7,6,3,0},   // right-left to top, back: right > bottom
                                   {0,1,4,1,2,5,8,7,6,3,0}});

//        vector<vector<int>> paths({{0,1,2,3,4,9,8,7,6,11,12,13,14,19,18,17,16,21,22,23,24,23,22,21,20,15,10,5,0},   // up-down to right, back: right > bottom
//                                   {0,1,2,3,  8,7,6,5,  10,11,12,13,  18,17,16,15,  20,21,22,23,24,  19,14,9,4,3,2,1,0},   // up-down to right, back: top > left
//                                   {0,5,10,15,20,  21,16,11,6,  7,12,17,22,  23,18,13,8,  9,14,19,24,19,14,9,4,3,2,1,0},   // right-left to top, back: top > left
//                                   {0,5,10,15,  16,11,6,1,  2,7,12,17,  18,13,8,3,  4,9,14,19,24,  23,22,21,20,15,10,5,0},   // right-left to top, back: right > bottom
//                                   {0, 1,2,3,4,9,14,19,24,23,18,13,8,7,12,17,22,21,20,15,16,11,10,5,6,5,0}});

    if (reversePaths)
    {
        for (size_t idx_path = 0, n = size(paths); idx_path < n; ++idx_path)
        {
            vector<int> newPath(paths[idx_path]);

            reverse(begin(newPath), end(newPath));

            paths.push_back(newPath);
        }
    }
    
    
    // ---------------------------------
    // --- Create routes on paths    ---
    // ---------------------------------
    
    double bestCost = numeric_limits<double>::max();
    vector<int> bestPath;
    
    bool solutionFound = false;
    
    for (int idx_path = 0; idx_path < size(paths); ++idx_path)
    {
        cout << idx_path << endl;
        
        auto const &path = paths[idx_path];
        
        for (int idx_rep = 0; idx_rep < nRep; ++idx_rep)
        {
            vector<int> path_nodes;
        
            int idx_from = getNodeFromTile(path[0]);
        
            path_nodes.push_back(idx_from);
        
            int maxTries = 200;
        
            bool failed = false;
            
            for (int idx = 1; idx < size(path); ++idx)
            {
                int const idx_tile = path[idx];
                
                int idx_to = -1;
                
                while (not edgeExists(idx_from, idx_to) and --maxTries > 0)
                    idx_to = getNodeFromTile(idx_tile);
                
                if (maxTries <= 0 or idx_from == idx_to)
                    failed = true;
                
                if (failed)
                    break;
                
                path_nodes.push_back(idx_to);
                
                idx_from = idx_to;
            }
            
            if (failed)
                continue;
                
            
            if (path_nodes.front() != path_nodes.back())
                path_nodes.push_back(path_nodes[0]);
            
            // Compute costs
            
            double cost = 0;
            
            for (int idx = 0; idx < size(path_nodes) - 1; ++idx)
                cost += getCost(path_nodes[idx], path_nodes[idx + 1]);
            
            if (cost < bestCost)
            {
                solutionFound = true;
                
                bestCost = cost;
                bestPath = path_nodes;
                
                // Print path
                
                cout << setw(5) << idx_path
                     << setw(5) << idx_rep
                     << setw(8) << bestCost << " - ";
                
                for (int idx: path_nodes)
                    cout << idx << " ";
                cout << endl;
            }
        }
    }
    
    cout << endl;

    // Set initial solution
    
    if (solutionFound)
    {
        for (int idx = 0; idx < size(bestPath) - 1; ++idx)
        {
            int const idx_from = bestPath[idx];
            int const idx_to   = bestPath[idx + 1];
            
            d_x[idx_from][idx_to].set(GRB_DoubleAttr_Start, 1);
        }
    }
}
