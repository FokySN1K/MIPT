/*
    Задача:

        В данном примере написана функция getMax, которая находит максимум из чисел в векторе.
        При этом вычисления проходят однопоточно.


        Вам нужно написать функцию

            uint64_t getMaxPar(int n, const std::vector<uint64_t>& v)

        которая будет делать то же самое, но только использовать для этого n потоков.
*/


#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdint>

using namespace std;




uint64_t getMax(const vector<uint64_t>& v)
{
    
    uint64_t result = v.at(0);
    for (auto el : v)
    {
        if (el > result)
            result = el;
    }

    

    return result;
}

void getMaxOne(vector<uint64_t>::const_iterator it1, vector<uint64_t>::const_iterator it2, uint64_t& result) {

    while (it1++ != it2) {
        if (*it1 > result) {
            result = *it1;
        }
    }

}

uint64_t getMax(int n, const vector<uint64_t>& v) {


    vector <uint64_t> results(n); // вектор максимумов каждого потока 
    // потоков будет адекватное кол-во
    // поэтому затем воспользуемся функцией getMax(vector)

    vector <thread> threads; // вектор потоков

    uint64_t adding = 0, sum = 0;

    adding = v.size() / n;


    // создаем потоки
    for (int i = 0; i < n; i++) {
        if (i + 1 != n) {
            threads.push_back(thread(getMaxOne, v.begin() + sum, v.begin() + sum + adding, ref(results[i])));
            sum += adding;
        }
        else {
            threads.push_back(thread(getMaxOne, v.begin() + sum, v.end(), ref(results[i])));
        }
    }

    for (int i = 0; i < n; i++) {
        threads[i].join();
    }

    return getMax(results);


}



int main()
{

    // генерируем числа 

    cout << "Generating numbers!" << endl;
    vector<uint64_t> numbers(50000000);
    numbers[0] = 123456789;
    for (size_t i = 1; i < numbers.size(); ++i)
    {
        numbers[i] = numbers[i - 1] * i + 1;
    }
    cout << "Numbers generated!" << endl;

    // обычная функция
    auto start = chrono::high_resolution_clock::now();

    uint64_t m = getMax(numbers);
    cout << "Maximum = " << m << endl;


    auto end = chrono::high_resolution_clock::now();
    cout << "Time to calclulate max = " << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " milliseconds." << endl;


    // функция с потоками
    start = chrono::high_resolution_clock::now();

    m = getMax(10, numbers);
    cout << "Maximum = " << m << endl;


    end = chrono::high_resolution_clock::now();
    cout << "Time to calclulate max = " << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " milliseconds." << endl;
    
}