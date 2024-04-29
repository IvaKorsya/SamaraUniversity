#include <vector>
#include <cmath>
#include <random>
#include <iostream>
#include <stdexcept>

#define MACHINE_WORD sizeof(size_t)
#define GOLDEN_RATIO ((sqrt(5)-1)/2)
#define PARAM_A GOLDEN_RATIO*MACHINE_WORD

template<class K, class V>
class HashTable{
    struct Node{
        K key;
        V value;
        bool is_filled;

        friend std::ostream& operator << (std::ostream& os, const Node& node){
            return os << "( " <<node.key << ", "<< node.value<<" )\n";
        }
    };

    std::vector<Node> _data;
    size_t _count_of_nodes;

    void _grow(){
        std::vector<Node> tmp;
        tmp.resize(_data.size()*1.7);
        std::swap(_data,tmp);
        _count_of_nodes=0;
        for(auto i=0;i<tmp.size();++i)
            if(tmp[i].is_filled) insert(tmp[i].key,tmp[i].value);
    }

    void _insert_or_assign(const K& key, const V& value, bool assign){
        double load_factor=_count_of_nodes/_data.size();
        if(load_factor>0.7) _grow();
        for(auto i=0;i<_data.size();++i){
            auto index= (size_t)std::fmod((_hash(key) + i * std::hash<K>{}(key)), _data.size());
            if(!_data[index].is_filled) {
                ++_count_of_nodes;
                _data[index]= Node{key,value,true};
                return;
            }
            if(_data[index].key==key) {
                if(assign) {
                    _data[index].value=value;
                    return;
                }
                else throw std::invalid_argument("update");
            }
        }
        _grow();
        if (assign) _insert_or_assign(key,value, 1);
        else _insert_or_assign(key,value, 0);
    }

    void _insert_with_count_of_collisions(const K& key, const V& value, size_t& collisions_count){
        for(auto i=0;i<_data.size();++i){
            auto index= (size_t)std::fmod(_hash(key) + (i * std::hash<K>{}(key)), _data.size());
            if(!_data[index].is_filled) {
                ++_count_of_nodes;
                _data[index]= Node{key,value,true};
                return;
            }
            ++collisions_count;
        }
    }

    void _swap(HashTable& other) noexcept{
        std::swap(_data,other.data);
        std::swap(_count_of_nodes,other._count_of_nodes);
    }

    [[nodiscard]] double _hash(K key) const noexcept{
        return std::floor(_data.size()*std::fmod(key*(PARAM_A / MACHINE_WORD), 1));
    }

public:
    explicit HashTable(size_t size): _count_of_nodes(0){
        _data.resize(size);
    }

    HashTable(const size_t size, const V& min_value, const V& max_value): _count_of_nodes(size){
        if(!size) throw std::invalid_argument("invalid size");
        _data.resize(size*2);
        for (auto i = 0; i < size; ++i) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(min_value, max_value);
            _data[i] = Node{i+1, dist(gen),true};
        }
    }

    HashTable(const size_t size, const size_t count_nodes, size_t& collision_count,[[maybe_unused]] bool mark): _count_of_nodes(count_nodes){
        _data.resize(size);
        for (auto i = 0; i < count_nodes; ++i){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<size_t> dist(0, 1043483);
            _insert_with_count_of_collisions(dist(gen), i, collision_count);
        }
    }

    HashTable(const HashTable& other): _count_of_nodes(0){
        _data.resize(other._data.size());
        for (const auto& node : other._data)
            if (node.is_filled) insert(node.key, node.value);
    }

    HashTable& operator=(HashTable other){
        _swap(other);
        return *this;
    }

    void insert(const K& key,const V& value){
        _insert_or_assign(key,value,0);
    }

    void insert_or_assign(const K& key, const V& value){
        _insert_or_assign(key,value,1);
    }

    bool contains(const V& value) noexcept{
        for(const auto& node : _data)
            if(node.is_filled && node.value==value) return true;
        return false;
    }

    V* search(const K& key) noexcept{
        for(auto i=0;i<_data.size();++i){
            auto index= (size_t)std::fmod((_hash(key) + i * std::hash<K>{}(key)), _data.size());
            if(_data[index].is_filled && _data[index].key == key) return &_data[index].value;
        }
        return nullptr;
    }

    size_t count(const K& key) {
        if(search(key)) return 1;
        return 0;
    }

    [[nodiscard]] size_t get_count_nodes() const noexcept{
        return _count_of_nodes;
    }

    bool erase(const K& key){
        for(auto i=0;i<_data.size();++i){
            auto index = (size_t)std::fmod((_hash(key) + i * std::hash<K>{}(key)), _data.size());
            if(_data[index].is_filled && _data[index].key==key){
                _data[index].is_filled=false;
                --_count_of_nodes;
                return true;
            }
        }
        return false;
    }

    void print(){
        for(const auto& node : _data)
            if (node.is_filled) { std::cout << node; }
    }

    bool operator==(const HashTable& other){
        if (_count_of_nodes != other._count_of_nodes) return false;
        for (size_t i = 0; i < std::min(_data.size(), other._data.size()); ++i){
            if (_data[i].is_filled && other._data[i].is_filled &&
            ((_data[i].key!=other._data[i].key) || (_data[i].value!=other._data[i].value))) return false;
        }
        return true;
    }

    bool operator!=(const HashTable& other){
        return !(this == other);
    }

    ~HashTable() = default;
};

void statistics(const size_t table_size){
    size_t count_nodes=26;
    size_t sum=0;
    for(auto i=0;i<100;++i){
        size_t collision_counter=0;
        HashTable<int,int> hash_table(table_size,count_nodes, collision_counter, true);
        sum+=collision_counter;
    }
    std::cout<<"size=" << table_size<< "    average count of collisions="<<sum/100<<"\n";
}