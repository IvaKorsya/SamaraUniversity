#include <graph.cc>
template<class V,class D=double>
std::pair<V,D> find_the_farthest_vertex(std::unique_ptr<Graph<V,D>> graph) {
    std::vector<std::pair<V,D>> distances;
    std::vector<V> vertices;
    std::vector<typename Graph<V,D>::Edge> edges;
    std::vector<typename Graph<V,D>::Edge> incoming_edges;
    auto sum_dist=0.0;
    graph->vertices(vertices);
    for(auto& vert: vertices){
        sum_dist=0.0;
        edges.clear();
        graph->edges(vert,edges);
        incoming_edges=graph->get_incoming_edges(vert);
        edges.insert(edges.end(),incoming_edges.begin(),incoming_edges.end());
        for(const auto& edge:edges){
            sum_dist+=edge.distance;
        }
        distances.push_back({vert,sum_dist/(static_cast<double>(graph->degree(vert) + incoming_edges.size()))});
    }
    std::pair<V, D> farthest_vert = distances[0];
    for (const auto& vert:distances) {
        if (farthest_vert.second < vert.second) farthest_vert = vert;
    }
    return farthest_vert;
}

int main(){
    auto char_graph = std::make_unique<Graph<char,double>>();
    char_graph->add_vertex('c');
    char_graph->add_vertex('b');
    char_graph->add_vertex('a');
    char_graph->add_vertex('d');
    char_graph->add_edge('a','c',16);
    char_graph->add_edge('a','b',1);
    char_graph->add_edge('a','d',5);
    char_graph->add_edge('b','c',8);
    char_graph->add_edge('b','d',9);
    auto result = find_the_farthest_vertex(std::move(char_graph));
    std::cout<< result.first <<" - "<<result.second;
    return 0;
}