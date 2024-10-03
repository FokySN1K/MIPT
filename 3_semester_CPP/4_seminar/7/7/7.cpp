#include <iostream>

using namespace std;

template <class T>
class Manager {

private:
	T* vec;

public:
	Manager() {
		vec = nullptr;
	}
	~Manager() {
		free(vec);
		cout << "Destructor" << endl;
	}
	void construct(const T& t) {
		*vec = t;
	}
	void allocate() {
		vec = (T*)malloc(sizeof(T));
	}
	void destruct() {
		free(vec);
		vec = (T*)malloc(sizeof(T));
	}
	void dealocate() {
		free(vec);
		vec = nullptr;
	}
	T& get() {
		return *vec;
	}


};



int main() {
	Manager <int> v;
	v.allocate();
	v.construct(1234);
	v.get() += 123;
	cout << v.get() << endl;
}