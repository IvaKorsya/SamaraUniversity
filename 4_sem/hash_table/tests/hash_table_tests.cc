#include <hash_table.cc>
#include <gtest/gtest.h>
#include <unordered_map>

TEST(hash_table_test,constructor_params){
    HashTable<int,int> hash(0);
    ASSERT_EQ(hash.get_count_nodes(),0);
}

TEST(hash_table_test,constructor_params_rand){
    HashTable<int,int> hash(5,6,7);
    ASSERT_EQ(hash.get_count_nodes(),5);
}

TEST(hash_table_test,insert){
    HashTable<int,int> hash(5,6,7);
    hash.insert(0,6);
    ASSERT_EQ(hash.get_count_nodes(),6);
    ASSERT_ANY_THROW(hash.insert(0,6));
}

TEST(hash_table_test,insert_or_assign){
    HashTable<int,int> hash(5,6,7);
    hash.insert_or_assign(0,6);
    ASSERT_EQ(hash.get_count_nodes(),6);
    hash.insert_or_assign(0,6);
    ASSERT_EQ(hash.get_count_nodes(),6);
}

TEST(hash_table_test,contains){
    HashTable<int,int> hash(5,6,7);
    hash.insert_or_assign(0,6);
    ASSERT_TRUE(hash.contains(6));
    ASSERT_FALSE(hash.contains(68594));
}

TEST(hash_table_test, search){
    HashTable<int,int> hash(5,6,7);
    hash.insert_or_assign(0,6);
    ASSERT_TRUE(hash.search(539028) == nullptr);
    ASSERT_EQ(*hash.search(0),6);
}

TEST(hash_table_test, count){
    HashTable<int,int> hash(5,6,7);
    hash.insert_or_assign(0,6);
    ASSERT_EQ(hash.count(0),1);
    ASSERT_EQ(hash.count(843948),0);
}

TEST(hash_table_test, erase){
    HashTable<int,int> hash(5,6,7);
    hash.insert_or_assign(0,6);
    ASSERT_TRUE(hash.erase(0));
    ASSERT_TRUE(hash.search(0) == nullptr);
    ASSERT_EQ(hash.get_count_nodes(),5);
}

TEST(hash_table_test, copy_constr){
    HashTable<int,int> hash(2);
    hash.insert_or_assign(3,4);
    HashTable<int,int> copy(hash);
    ASSERT_TRUE(copy==hash);
}

TEST(hash_table_test, overloaded_eq){
    HashTable<int,int> hash(2);
    hash.insert_or_assign(3,4);
    HashTable<int,int> copy=hash;
    ASSERT_TRUE(copy==hash);
}

TEST(hash_table_test, double_hash_table){
    HashTable<double,double> hash(2);
    hash.insert_or_assign(3.0,4.0);
    ASSERT_TRUE(hash.contains(4.0));
    ASSERT_TRUE(hash.search(3.0));
}

TEST(hash_table_test, float_table){
    HashTable<float,float> hash(2);
    hash.insert_or_assign(3.0f,4.0f);
    ASSERT_TRUE(hash.contains(4.0));
    ASSERT_TRUE(hash.search(3.0));
}

TEST(hash_table_test, char_table){
    HashTable<char,char> hash(2);
    hash.insert_or_assign('c','c');
    ASSERT_TRUE(hash.contains('c'));
    ASSERT_TRUE(hash.search('c'));
}

TEST(stat_test, get_stat){
    for(auto i=25; i < 476;i+=50){
        statistics(i);
    }
}
