#include <iostream>
#include "miptstring.hpp"


int main() {
	mipt::String a = "Cat";
	std::cout << a;


	mipt::String *b = new mipt::String[1];
	(*b) = "Dog";
	std::cout << *b;
	delete[] b;

	mipt::String* d = new mipt::String[2]{"Dog", "Cat"};
	d[0] = "Dog";
	std::cout << d[0] << d[1];
	delete[] d;

	char* x = (char*)malloc(sizeof(mipt::String));
	mipt::String* px = new(x) mipt::String{ "Elephant" };
	std::cout << px[0];
	px->~String();
	free(px);
}