#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <assert.h>
using namespace std;

class Number
{
private:
    static const int base = 100;
    std::size_t size;
    std::size_t capacity;
    char* data;

public:
    Number();
    Number(long long a);
    Number(const Number& left);
    Number(const char* str);
    ~Number();

    Number& operator =(const Number& left);
    Number operator +(const Number& left) const;
    void operator +=(const Number& left);
    Number operator *(const Number& left) const;
    void operator *=(const Number& left);
    char operator [](int n)const;
    bool operator >(const Number& left) const;
    bool operator <(const Number& left) const;

    int get_size();

    void divide_by_2();
    friend bool isEven(const Number& right);
    friend ostream& operator<<(ostream& stream, const Number& right);
};