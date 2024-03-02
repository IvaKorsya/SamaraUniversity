#include <list/list.h>
#include <gtest/gtest.h>
#include <iostream>
//1
TEST(list_tests,default_constructor) {
	linked_list<int> list = linked_list<int>();
	ASSERT_EQ(list[0].value, 0);
	ASSERT_EQ(list.get_size(), 1);
}
//2
TEST(list_tests, random_value_constructor) {
	linked_list<int> list = linked_list<int>(3);
	ASSERT_EQ(list.get_size(), 3);
}
//3
TEST(list_tests, add_to_tail_value) {
	linked_list<int> list = linked_list<int>(3);
	list.add_to_tail(9);
	ASSERT_EQ(list[3].value, 9);
	ASSERT_EQ(list.get_size(), 4);
}
//4
TEST(list_tests, add_to_tail_list) {
	linked_list<int> list = linked_list<int>(3);
	linked_list<int> list2 = linked_list<int>(1);
	list2.add_to_tail(8);
	list.add_to_tail(list2);
	ASSERT_EQ(list[4].value, 8);
	ASSERT_EQ(list.get_size(), 5);
}
//5
TEST(list_tests, add_to_head_value) {
	linked_list<int> list = linked_list<int>(3);
	list.add_to_head(5);
	ASSERT_EQ(list[0].value, 5);
	ASSERT_EQ(list.get_size(), 4);
}
//6
TEST(list_tests, copy_constr) {
	linked_list<int> list = linked_list<int>();
	auto list_copy(list);
	list_copy.add_to_tail(5);
	ASSERT_EQ(list_copy[0].value, 5);
	ASSERT_EQ(list_copy.get_size(), 1);
	list_copy.add_to_tail(4);
	ASSERT_EQ(list_copy[1].prev->value,5);
}
//7
TEST(list_tests, operator_eq) {
	linked_list<int> list = linked_list<int>(3);
	list.add_to_head(2);
	auto list_copy=list;
	ASSERT_EQ(list_copy[0].value, 2);
	ASSERT_EQ(list_copy.get_size(), 4);
}
//8
TEST(list_tests,add_to_head_list) {
	linked_list<int> list = linked_list<int>(3);
	linked_list<int> list2 = linked_list<int>(3);
	list2.add_to_tail(7);
	list.add_to_head(list2);
	ASSERT_EQ(list[3].value, 7);
	ASSERT_EQ(list.get_size(), 7);
}
//9
TEST(list_tests, pop_head_1_el) {
	linked_list<int> list = linked_list<int>();
	list.add_to_head(2);
	list.pop_head();
	ASSERT_EQ(list[0].value, 0);
	ASSERT_EQ(list.get_size(), 1);
}
//10
TEST(list_tests, get_tail) {
	linked_list<int> list = linked_list<int>();
	list.add_to_tail(7);
	ASSERT_EQ(list.get_tail()->value, 7);
}
//11
TEST(list_tests, pop_tail) {
	linked_list<int> list = linked_list<int>();
	list.add_to_head(2);
	list.add_to_tail(5);
	list.pop_tail();
	ASSERT_EQ(list[0].value, 2);
	ASSERT_EQ(list.get_size(), 1);
}
//12
TEST(list_tests, delete_node) {
	linked_list<int> list = linked_list<int>();
	list.add_to_head(5);
	list.add_to_tail(5);
	list.add_to_tail(3);
	list.add_to_tail(5);
	list.add_to_tail(4);
	list.add_to_tail(5);
	list.add_to_tail(5);
	list.delete_node(5);
	ASSERT_EQ(list[0].value, 3);
	ASSERT_EQ(list[1].value, 4);
	ASSERT_EQ(list.get_size(), 2);
}
//13
TEST(list_tests, sum_of_lists) {
	linked_list<int> list = linked_list<int>();
	linked_list<int> list2 = linked_list<int>();
	list.add_to_head(6);//663
	list.add_to_tail(6);
	list.add_to_tail(3);
	list2.add_to_tail(4);//491
	list2.add_to_tail(9);
	list2.add_to_tail(1);//answer 1154
	auto sum_lists = sum(list2, list);
	ASSERT_EQ(sum_lists[0].value, 1);
	ASSERT_EQ(sum_lists[1].value, 1);
	ASSERT_EQ(sum_lists[2].value, 5);
	ASSERT_EQ(sum_lists[3].value, 4);
	ASSERT_EQ(sum_lists.get_size(), 4);
}
//13
TEST(list_tests, sum_of_lists_with_null_list) {
	linked_list<int> list = linked_list<int>();
	linked_list<int> list2 = linked_list<int>();
	list.add_to_head(6);//663
	list.add_to_tail(6);
	list.add_to_tail(3);
	auto sum_lists = sum(list2, list);
	ASSERT_EQ(sum_lists[0].value, 6);
	ASSERT_EQ(sum_lists[1].value, 6);
	ASSERT_EQ(sum_lists[2].value, 3);
	ASSERT_EQ(sum_lists.get_size(), 3);
}
//14
TEST(list_tests, pop_head_2_el) {
	linked_list<int> list = linked_list<int>();
	list.add_to_head(2);
	list.add_to_head(2);
	list.pop_head();
	ASSERT_EQ(list[0].value, 2);
	ASSERT_EQ(list.get_size(), 1);
}
//14
TEST(list_tests, pop_head_5_el) {
	linked_list<int> list = linked_list<int>();
	list.add_to_head(2);
	list.add_to_head(2);
	list.add_to_head(2);
	list.add_to_head(2);
	list.add_to_head(2);
	list.pop_head();
	list.pop_head();
	list.pop_head();
	list.pop_head();
	ASSERT_EQ(list[0].value, 2);
	ASSERT_EQ(list.get_size(), 1);
}

