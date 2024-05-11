#include <graph.cc>
#include <gtest/gtest.h>

class GraphFixture: public ::testing::Test{
protected:
    std::unique_ptr<Graph<int,double>> graph;
    std::unique_ptr<Graph<char,double>> char_graph;

    void SetUp() override{
        graph = std::make_unique<Graph<int,double>>();

        char_graph = std::make_unique<Graph<char,double>>();
        char_graph->add_vertex('c');
        char_graph->add_vertex('b');
        char_graph->add_vertex('a');
        char_graph->add_vertex('d');
        char_graph->add_edge('c','c',5);
        char_graph->add_edge('c','b',5);
        char_graph->add_edge('b','d',5);
        char_graph->add_edge('c','a',8);
        char_graph->add_edge('a','d',1);
        char_graph->add_edge('b','a',7);
    }
public:
    ~GraphFixture() override = default;
};

TEST_F(GraphFixture,add_vertex){
    ASSERT_TRUE(graph->add_vertex(3));
    ASSERT_EQ(graph->order(),1);
    ASSERT_TRUE(graph->has_vertex(3));
    ASSERT_FALSE(graph->add_vertex(3));
}

TEST_F(GraphFixture,add_edge){
    ASSERT_NO_THROW(char_graph->add_edge('b','c',1));
    ASSERT_THROW(char_graph->add_edge('d','q',1),std::invalid_argument);
    ASSERT_THROW(char_graph->add_edge('b','c',-10),std::invalid_argument);
    ASSERT_TRUE(char_graph->has_edge('b','c'));
    ASSERT_TRUE(char_graph->has_edge({'b','c',1}));
}

TEST_F(GraphFixture,delete_vertex){
    ASSERT_TRUE(char_graph->remove_vertex('b'));
    ASSERT_FALSE(char_graph->remove_vertex('q'));
    ASSERT_EQ(char_graph->order(),3);
}

TEST_F(GraphFixture,delete_edge){
    ASSERT_TRUE(char_graph->remove_edge('c','b'));
    ASSERT_TRUE(char_graph->remove_edge({'c','c',5}));
    ASSERT_FALSE(char_graph->remove_edge({'c','c',5}));
}

TEST_F(GraphFixture,vertex_degree){
    ASSERT_EQ(char_graph->degree('c'),3);
    ASSERT_EQ(char_graph->degree('d'),0);
    ASSERT_THROW(char_graph->degree('q'),std::invalid_argument);
}

TEST_F(GraphFixture, walk){
    char_graph->walk('c',[](char vert){std::cout<<vert<<" ";});
    std::cout<<"\n";
    std::vector<char> result;
    char_graph->walk('c',[&result](char vert){result.push_back(vert);});
    for(const auto& vert:result) std::cout<<vert<<" ";
}

TEST_F(GraphFixture, shortest_path){
    auto result=char_graph->shortest_path('c','d');
    std::cout<<"\nshortest path from 'c' to 'd':\n";
    for(const auto& edge:result) std::cout<<edge;
}

