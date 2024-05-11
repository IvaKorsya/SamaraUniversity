#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <set>
#include <queue>
#include <limits>

template< class V, class D = double>
class Graph {
public:
    struct Edge {
        V from, to;
        D distance;

        friend std::ostream &operator<<(std::ostream& os, const Edge &edge) {
            return os << "(" << edge.from << " ," << edge.to << ") = " << edge.distance << "\n";
        }
    };
private:
    std::set<V> _vertices;
    std::unordered_map<V,std::vector<Edge>> _edges;

    void _swap(Graph &other) noexcept {
        std::swap(_edges, other._edges);
    }

    bool _has_edge(const V& from, const V& to, const D& distance) const{
        if(!_vertices.contains(to) || !_vertices.contains(to)) return false;
        if(distance > -1){
            return std::any_of(_edges.at(from).begin(),
                               _edges.at(from).end(),
                               [to,distance](const Edge& ed) { return ed.to == to && ed.distance == distance;});
        }
        return std::any_of(_edges.at(from).begin(),
                           _edges.at(from).end(),
                           [to](const Edge& edge){ return edge.to == to;});
    }

    bool _remove_edge(const V& from, const V& to, const D& distance){
        if (!_edges.contains(from) || !_vertices.contains(to)) return false;
        auto cnt_erased=0;
        if(distance > -1)
            cnt_erased += std::erase_if(_edges[from],
                                        [to,distance](const Edge &edge)
                                        {return edge.to == to && edge.distance == distance;});
        else
            cnt_erased += std::erase_if(_edges[from],
                                            [to](const Edge &edge)
                                            {return edge.to == to;});
        if(cnt_erased) return true;
        return false;
    }

public:
    Graph() = default;

    Graph(const Graph& other){
        for(const auto& vert: other._vertices){
            add_vertex(vert);
            for(const auto& edge: other._edges[vert]){
                add_edge(edge);
            }
        }
    }

    Graph& operator=(Graph other){
        _swap(other);
        return *this;
    }

    bool operator==(const Graph& other){
        return _vertices=other._vertices && _edges=other._edges;
    }

    bool operator!=(const Graph& other){
        return !(this == other);
    }

    bool add_vertex(const V& vert) noexcept{
        if (_vertices.insert(vert).second) {
            _edges.insert({vert, {}});
            return true;
        }
        return false;
    }

    [[nodiscard]] size_t order() const{
        return _vertices.size();
    }

    bool has_vertex(const V& vert) const noexcept{
        return _vertices.contains(vert);
    }

    [[nodiscard]] std::vector<Edge> get_incoming_edges(const V& vert) const{
        std::vector<Edge> incoming_vert;
        for(const auto& v:_vertices){
            for(const auto& edge: _edges.at(v)){
                if (edge.to == vert) incoming_vert.push_back(edge);
            }
        }
        return incoming_vert;
    }

    bool remove_vertex(const V& vert){
        if(_vertices.erase(vert)){
            _edges.erase(vert);
            for(auto edge: get_incoming_edges(vert)){
                std::erase_if(_edges[edge.from],[vert](const Edge& edge) { return edge.to == vert;});
            }
            return true;
        }
        return false;
    }

    void vertices(std::vector<V>& vertices) const noexcept{
        for(const auto& vert:_vertices) vertices.push_back(vert);
    }

    void edges(const V& vert,std::vector<Edge>& edges) const noexcept{
        for(const auto& edge: _edges.at(vert)) edges.push_back(edge);
    }

    [[maybe_unused]] void edges(std::vector<Edge>& edges) const noexcept{
        for(const auto& vert:_vertices){
            auto ed=_edges.at(vert);
            for(const auto& edge:ed) edges.push_back(edge);
        }
    }

    void add_edge(const V& from, const V& to,const D& distance){
        if(!_vertices.contains(from)) throw std::invalid_argument("from is not exist");
        if(!_vertices.contains(to)) throw std::invalid_argument("to is not exist");
        if(distance < 0) throw std::invalid_argument("only unsigned distance");
        _edges[from].push_back({from,to,distance});
    }

   bool has_edge(const V& from, const V& to) const{
        return _has_edge(from,to,-1);
   }

   bool has_edge(const Edge& edge) const{
       return _has_edge(edge.from,edge.to,edge.distance);
   }

  bool remove_edge(const V& from, const V& to){
      return _remove_edge(from,to,-1);
  }

  bool remove_edge(const Edge& edge){
      return _remove_edge(edge.from,edge.to,edge.distance);
  }

  size_t degree(const V& vert) const{
      if (_vertices.contains(vert)) return _edges.at(vert).size();
      throw std::invalid_argument("vert is not exist");
  }

  void walk(const V& start,const std::function<void(const V& )>& action) const{
      std::unordered_map<V, bool> visited;
      for (const auto &vert: _vertices) visited[vert] = false;
      std::queue<V> queue;
      queue.push(start);
      while(!queue.empty()){
          auto current=queue.front();
          queue.pop();
          if(!visited[current]) {
              visited[current] = true;
              action(current);
              for (const auto &edge: _edges.at(current)) if (!visited[edge.to]) queue.push(edge.to);
          }
      }
  }

  std::vector<Edge> shortest_path(const V& start,const V& end) const {
      if (!_vertices.contains(start) || !_vertices.contains(end)) throw std::invalid_argument("not found");
      std::unordered_map<V, D> distances;
      for (const auto &vert: _vertices) distances[vert] = std::numeric_limits<D>::infinity();
      distances[start] = 0;

      std::vector<Edge> path;
      std::priority_queue<std::pair<D, V>> priority_queue;
      priority_queue.push({0, start});

      std::unordered_map<V, V> prev;
      while (!priority_queue.empty()) {
          std::pair<D, V> current = priority_queue.top();
          priority_queue.pop();

          for (const auto &edge: _edges.at(current.second)) {
              D new_dist = current.first + edge.distance;
              if (new_dist < distances[edge.to]) {
                  prev[edge.to] = current.second;
                  distances[edge.to] = new_dist;
                  priority_queue.push({new_dist, edge.to});
              }
          }
      }
      if (distances[end] == std::numeric_limits<D>::infinity()) return {};

      V current = end;
      while (current != start) {
          V prev_v = prev[current];
          D dist = distances[current] - distances[prev_v];
          path.push_back(Edge{ prev_v, current, dist });
          current = prev_v;
      }
      reverse(path.begin(), path.end());
      return path;
  }
};