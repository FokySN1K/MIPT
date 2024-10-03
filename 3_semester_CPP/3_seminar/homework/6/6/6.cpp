#include <iostream>
#include <string_view>
using namespace std;

int main() {
	{
		int* x = new int{ 123 };
		cout << *x << endl;
		delete x;
	}
	{
		string* x = new string{ "Cats and Dogs" };
		cout << *x << endl;
		delete x;
	}
	{
		int* x = new int[5]{10, 20, 30, 40, 50};
		cout << x[4] << endl;
		delete[] x;
	}
	{
		string* x = new string[3]{"Cat", "Dog", "Mouse"};
		cout << x[2] << endl;
		delete[] x;
	}	
	{
		string* x = new string[3]{ "Cat", "Dog", "Mouse" };
		string_view* s = new string_view[3]{x[0], x[1], x[2]};
		cout << s[1] << endl;
		delete[] s;
		delete[] x;
	}

}