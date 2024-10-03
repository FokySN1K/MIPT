#include <iostream>
using namespace std;

struct Book
{
	char title[100];
	int pages;
	float price;
};

void addPrice(Book& a, float x) {
	a.price += x;
}

bool isExpensive(const Book& a) {
	if (a.price > 1000) {
		return true;
	}
	return false;
}

int main()
{
	Book a = { "231", 4, 5 };
	addPrice(a, 3);
	cout << isExpensive(a);
}
