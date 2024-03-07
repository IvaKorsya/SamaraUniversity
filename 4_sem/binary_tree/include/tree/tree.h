#include <initializer_list>
#include <vector>
#include <stack>
struct node {
	int data;
	node* left;
	node* right;
	node(int val,node* left,node* right);
};

class set_iter {
	std::stack<node*> _stack;
	node* _current;
public:
	set_iter(node* node);
	node* operator*();
	bool operator==(const set_iter& second);
	bool operator!=(const set_iter& second);
	void next();
	bool has_next();
};

class my_set {
	node* _root;

	void _print(const node* root) const;
	void _clear(node* root);
	node* _copy(node* root);
	bool _equal(const node* first, const node* second) const;
	bool _erase(node*& node_, const int key);
	

public:
	my_set();
	my_set(const int val);
	my_set(const my_set& other);
	my_set(std::initializer_list<int> values);

    bool operator==(const my_set& second);
	bool operator!=(const my_set& second);
	my_set& operator=(my_set other);
	int get_root_value() const;
	node* get_root() const;

	bool erase(const int key);
	bool equal(const my_set& second) const;
	void swap(my_set& other) noexcept;
	void print() const;
	bool contains(const int key) const;
	bool insert(const int key);

	set_iter begin();
	set_iter end();

	~my_set();
};

my_set intersection(const my_set& first, const my_set& second);
my_set difference(const my_set& first,const my_set& second);

