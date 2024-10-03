#include "complex.h"


Complex operator+(const Complex& a, const Complex& b);
Complex operator-(const Complex& a, const Complex& b);
Complex operator*(const Complex& a, const Complex& b);
Complex operator/(const Complex& a, const Complex& b);
Complex& operator+=(Complex& a, const Complex& b);
Complex operator-(const Complex& a);
Complex operator+(const Complex& a);
// Унарный оператор *
// То есть если z - комплексное число x + iy, то *z = x - iy
// Оператор сопряжения
Complex operator*(const Complex& a);


// Число + комплексное число (в таком порядке)
Complex operator+(float a, const Complex& b);
// Комплексное число + число
Complex operator+(const Complex& a, float b);

// Число - комплексное число (в таком порядке)
Complex operator-(float a, const Complex& b);
// Комплексное число - число
Complex operator-(const Complex& a, float b);



// Комплексное число * число
Complex operator*(const Complex& a, float b);

// Число * комплексное число
Complex operator*(float a, const Complex& b);

// Комплексное число / число
Complex operator/(const Complex& a, float b);

// Число / комплексное число
Complex operator/(float a, const Complex& b);

// Перегружаем оператор<< между типами 
// std::ostream (такой тип имеет std::cout) и Complex
// Обратите внимание, что мы возвращаем ссылку на ostream
// Таким образом результатом выражения  cout << a  будет cout
// Поэтому можно делать так: cout << a << b << c ...
std::ostream& operator<<(std::ostream& out, const Complex& a);

std::istream& operator>>(std::istream& in, Complex& c);
float abs(const Complex& a);
Complex exp(const Complex& a);

Complex sin(const Complex& a);

Complex cos(const Complex& a);