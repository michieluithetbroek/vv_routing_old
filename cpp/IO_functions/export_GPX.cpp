//
//  export_GPX.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 03/05/2022.
//

#include "IO_functions.hpp"

void export_GPX(vector<int> const &route)
{
    string const fileName = "test.gpx";
    
    ofstream file(fileName);
    
    if (not file.is_open())
        throw string("export_GPX - Could not open file: " + fileName);
    
    for (int const idx_node: route)
    {
        int const lat = 1;
        int const lon = 2;
        int const time = 3;
        
        file << "<trkpt lat=" << lat << " lon=" << lon << ">\n"
             << "<time>" << time << "</time>\n"
             << "</trkpt>\n";
    }
    
    
}
