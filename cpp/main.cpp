//
//  main.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 13/04/2022.
//

#include "main.h"

int main(int argc, const char * argv[])
try
{
    vector<Edge> edges = read_edges();
    auto tileSets = read_tileSets();

    for (auto v: tileSets)
    {
        for (auto v2: v)
            cout << v2 << " ";
        cout << endl;
    }
    
    std::cout << "Hello, World!\n";
    
    return 0;
}
catch (std::string const &e)
{
    cout << e << endl;
}
