//
//  InitOSM.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 05/05/2022.
//

#include "initOSM.ih"

using index_t = osmium::index::map::SparseMemArray<osmium::unsigned_object_id_type, osmium::Location>;
using cache_t = osmium::handler::NodeLocationsForWays<index_t>;

struct MyHandler: public osmium::handler::Handler
{
    struct Node
    {
        int const idx_node;
        int const idx_way;
        
        double const lon;
        double const lat;
        
        int const tile_x;
        int const tile_y;
        
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
    };

    unsigned long int d_nWays_processed  = 0;
    unsigned long int d_nWays_cross      = 0;
    unsigned long int d_nNodes_processed = 0;
    
    std::vector<Node> d_nodes;
    
    // This function is called by Osmium for each way object
    
    void way(osmium::Way const &way)
    {
        ++d_nWays_processed;
        
        int constexpr zoom = 14;
        
        if (not way.visible())
            return;
        
        if (way.deleted())
            return;
        
        
        
        //
        // Only process specific highway types
        //
        
        osmium::TagsFilter filter{false};
        
        filter.add_rule(true, "highway", "primary");
        filter.add_rule(true, "highway", "secondary");
        filter.add_rule(true, "highway", "tertiary");
        filter.add_rule(true, "highway", "unclassified");
        filter.add_rule(true, "highway", "service");
        
        filter.add_rule(true, "highway", "cycleway");
        
        filter.add_rule(true, "highway", "residential");
        filter.add_rule(true, "highway", "living_street");
        
        if (not osmium::tags::match_any_of(way.tags(), filter))
            return;
        
        
        
        //
        // Process all nodes on this way
        //
        
        osmium::NodeRefList const &nodes = way.nodes();
        
        size_t const nNodes = nodes.size();
        
        d_nNodes_processed += nNodes;
        
//        cout << way.tags() << '\n';
        
        for (size_t idx = 0; idx < nNodes; ++idx)
        {
            size_t const idx_prev = (idx > 0 ? idx - 1 : 0);
            size_t const idx_next = (idx < nNodes - 1 ? idx + 1 : nNodes - 1);
            
            osmium::NodeRef const &node_prev = nodes[idx_prev];
            osmium::NodeRef const &node_curr = nodes[idx];
            osmium::NodeRef const &node_next = nodes[idx_next];
            
            osmium::geom::Tile const tile_prev {uint32_t(zoom), node_prev.location()};
            osmium::geom::Tile const tile_curr {uint32_t(zoom), node_curr.location()};
            osmium::geom::Tile const tile_next {uint32_t(zoom), node_next.location()};
            
            // Save node if previous or next node lies in a different tile
            
            if (tile_curr.x != tile_prev.x or
                tile_curr.x != tile_next.x or
                tile_curr.y != tile_prev.y or
                tile_curr.y != tile_next.y)
            {
                d_nodes.emplace_back(node_curr.ref(), way.id(),
                                     node_curr.lon(), node_curr.lat(),
                                     tile_curr.x, tile_curr. y);
            }
        }
    }
};

InitOSM::InitOSM()
{
    index_t index;
    cache_t cache{index};
    
    string const fileName = "/Users/michiel/Dropbox/programming/OSM_data/netherlands-latest.osm.pbf";
//    string const fileName = "/Users/michiel/Dropbox/programming/OSM_data/groningen-latest.osm.pbf";
    
    osmium::io::File input_file{fileName};
    osmium::io::Reader reader{input_file,
        osmium::osm_entity_bits::node |
        osmium::osm_entity_bits::way};
    
    auto const start = std::chrono::system_clock::now();
    
    MyHandler handler;
    osmium::apply(reader, cache, handler);
    
    cout << "nWays processed:     " << handler.d_nWays_processed  << '\n'
         << "nWays cross tile:    " << handler.d_nWays_cross      << '\n'
         << "nNodes processed:    " << handler.d_nNodes_processed << '\n'
         << "nNodes final:        " << handler.d_nodes.size()     << '\n';
    
    auto const end = std::chrono::system_clock::now();
    
    cout << "Time: " << (static_cast<double>((end - start).count())) / 1000000 << endl;
    
    
//    // Initialize progress bar, enable it only if STDERR is a TTY.
//    osmium::ProgressBar progress{reader.file_size(), osmium::isatty(2)};
}
