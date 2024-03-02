#include <iostream>
#include <string>
using namespace std;
class Vector
{
public:
	float x, y;

	Vector() :x(0), y(0) {};
	Vector(float x, float y) : x(x), y(y) {};
    
	Vector& operator+=(Vector const &b){//must "const"
		x += b.x;
		y += b.y;
		return *this;
	}

	Vector operator+(const Vector& b)const {//must "const"
		Vector c(*this);
		c += b;
		return c;
	}
};

Vector& operator++(Vector& v){
	++v.x;
	++v.y;
	return v;
}

Vector operator++(Vector& v, int){
	Vector v_cp(v);
	++v;
	return v_cp;
}

class String{
public:
	static const int CAPACITY = 512;
private:
	char _str[CAPACITY];
	int _length;
public:
	String() :_str("0"), _length(0) {};

	String(const char* str): _length(strlen(str))
	{
		if (_length >= CAPACITY) {
			throw runtime_error("");
		}
		strcpy_s(_str, str);
	}

	int get_len()const {
		return _length;
	}

	char& operator[](int ind) {
		if (ind < 0 || ind >= _length) {
			throw runtime_error("");
		}
		return _str[ind];
	}

	char operator[](int ind) const{
		if (ind < 0 || ind >= _length) {
			throw runtime_error("");
		}
		return _str[ind];
	}

	String& operator+=(const String& n_str) {
		if (_length + n_str._length >= CAPACITY) {
			throw runtime_error("");
		}
		strcat_s(_str, n_str._str);
		return *this;
	}
};

int main() {
	return 0;
}

