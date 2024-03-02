#include <random>
#include <stdexcept>
#include <iostream>
template<class T>
class linked_list {
	struct node {
		T value;
		node* prev;
		node* next;

		node(T value, node* prev, node* next) : value(value), prev(prev), next(next) {};
	};
	node* _head;
	size_t _size;
public:
	linked_list() : _head(new node(NULL, nullptr, nullptr)), _size(1) {};

	linked_list(size_t size) : _size(size) {
		if (size <= 0) _size = 1;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist_for_head(1, 9);
		std::uniform_int_distribution<> dist(0, 9);
		_head = new node(dist_for_head(gen), nullptr, nullptr);
		auto tmp = _head;
		size_t cur_ind = 1;
		while (cur_ind++ < size) {
			tmp->next = new node(dist(gen), tmp, nullptr);
			tmp = tmp->next;
		}
	}

	linked_list(const linked_list& list) : _head(nullptr), _size(0) {
		this->add_to_tail(list);
	}

	linked_list& operator=(const linked_list& list) {
		auto tmp = _head;
		_size = 0;
		while (tmp) {
			_head = _head->next;
			delete tmp;
			tmp = _head;
		}
		this->add_to_tail(list);
		return *this;
	}

	const node& operator[](size_t index) const {
		if (index < 0 || index >= _size) throw std::invalid_argument("index out of the range");
		size_t cur_ind = 0;
		node* tmp = _head;
		while (cur_ind++ != index) {
			tmp = tmp->next;
		}
		return *tmp;
	}

	node& operator[](size_t index) {
		if (index < 0 || index >= _size) throw std::invalid_argument("index out of the range");
		size_t cur_ind = 0;
		node* tmp = _head;
		while (cur_ind++ != index) {
			tmp = tmp->next;
		}
		return *tmp;
	}

	void add_to_head_for_sum(const T& value) {
		++_size;
		if (_head->value == 0 && _size==2) {
			_head = new node(value, nullptr, nullptr);
			_size = 1;
			return;
		}
		auto tmp = _head;
		_head = new node(value, nullptr, tmp);
		tmp->prev = _head;
	}

	void add_to_head(const T& value) {
		if (value <1  || value  >9) throw std::invalid_argument("accepted 1 to 9");
		++_size;
		
		if (_head->value == 0) {
			_head = new node(value, nullptr, nullptr);
			_size = 1;
			return;
		}
		auto tmp = _head;
		_head = new node(value, nullptr, tmp);
		tmp->prev = _head;
	}

	void add_to_head(const linked_list& list) {
		auto new_head = list;
		new_head.add_to_tail(*this);
		*this = new_head;
	}

	void add_to_tail(const T& value) {
		++_size;
		if (value < 0 || value > 9) throw std::invalid_argument("0 to 9");
		if (!_head || _head->value == 0) {
			_head = new node(value, nullptr, nullptr);
			_size = 1;
			return;
		}
		auto tmp = _head;
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = new node(value, tmp, nullptr);
	}

	void add_to_tail(const linked_list& list) {
		_size += list._size;
		auto tmp2 = list._head;
		node* tmp;
		if (!_head) {
			_head = new node(list._head->value, nullptr, nullptr);
			tmp = _head;
			tmp2 = tmp2->next;
		}
		else {
			tmp = this->get_tail();
		}
		while (tmp2) {
			tmp->next = new node(tmp2->value, tmp, nullptr);
			tmp2 = tmp2->next;
			tmp = tmp->next;
		}
	}

	void pop_head() {
		if (_size == 1) {
			_head->value = 0;
			return;
		}	
		auto new_head = _head->next;
		if (new_head != nullptr)
			new_head->prev = nullptr;
		delete _head;
		_head = new_head;
		--_size;
		
	}

	void pop_tail() {
		--_size;
		if (_size == 0) {
			*this = linked_list();
			return;
		}
		auto tmp = _head;
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->prev->next = nullptr;
		delete tmp;
	}

	void delete_node(const T& value) {
		if (value < 0 || value>9) throw std::invalid_argument("0 to 9");
		auto tmp = _head;
		while (tmp) {
			if (tmp->value == value) {
				auto ptr_tmp = tmp;
				tmp = tmp->next;
				if(!ptr_tmp->prev) _head = ptr_tmp->next;
				else ptr_tmp->prev->next = ptr_tmp->next;
				if (ptr_tmp->next) ptr_tmp->next->prev = ptr_tmp->prev;
				delete ptr_tmp;
				--_size;
			}
			else tmp = tmp->next;
		}
	}
	
	friend std::ostream& operator<<(std::ostream& os, const linked_list& list) {
		os << "{ ";
		auto tmp = list._head;
		while (tmp) {
			os << tmp->value << " ";
			tmp = tmp->next;
		}
		os << "}";
		return os;
	}

	~linked_list() {
		while (_head) {
			auto tmp = _head;
			_head = _head->next;
			delete tmp;
		}
	}

	size_t get_size() const {
		return _size;
	}

	node* get_head() const {
		return _head;
	}

	node* get_tail() const {
		auto tmp = _head;
		while (tmp->next) {
			tmp = tmp->next;
		}
		return tmp;
	}
};


template<class T>
linked_list<T> sum(const linked_list<T>& first, const linked_list<T>& second) {
	linked_list<T> result=linked_list<T>();
	T ten = 0;
	auto tmp = first.get_tail();
	auto tmp2 = second.get_tail();
	while (tmp || tmp2 || ten!=0) {
		T sum = ten;
		if (tmp) {
			sum += tmp->value;
			tmp = tmp->prev;
		}
		if (tmp2) {
			sum += tmp2->value;
			tmp2 = tmp2->prev;
		}
		ten = sum / 10;
		result.add_to_head_for_sum(sum % 10);
	}
	return result;
} 
