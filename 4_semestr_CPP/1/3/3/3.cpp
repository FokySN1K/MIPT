#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdint>

using std::cout, std::endl, std::size_t;
using namespace std::chrono_literals;

template <typename RandIt, typename Comparator>
bool issorted(RandIt first, RandIt last, Comparator comp) {
    if (first != last) {
        auto next = first;
        while (++next != last) {
            if (comp(*next, *first)) {
                return false;
            }
            first = next;
        }
    }
    return true;
}

template <typename RandIt, typename Comparator>
void parallelSort(int n, RandIt start, RandIt finish, Comparator comp) {
    if (n == 1) {
        std::sort(start, finish, comp);
        //cout << finish - start << endl;
    }
    else {
        if (start == finish) return;
        auto pivot = *start;
        RandIt middle = std::partition(start, finish, [pivot, comp](const auto& t) {return comp(t, pivot); });
        int nl = std::round((double)((middle - start) * n) / (finish - start));
        if (nl == 0) {
            nl = 1;
        }
        int nr = n - nl;
        if (nr == 0) {
            nr = 1;
            nl--;
        }
        /*
        int nl = n / 2;
        int nr = n - nl;
        */
        auto f = std::async(std::launch::async, parallelSort<RandIt, Comparator>, nl, start, middle, comp);
        parallelSort(nr, middle, finish, comp);
        f.get();
    }
}

int main()
{

    cout << "Generating numbers!" << endl;
    std::vector<uint64_t> numbers(2e7);
    numbers[0] = 123456789;
    for (size_t i = 1; i < numbers.size(); ++i)
    {
        numbers[i] = numbers[i - 1] * i + 1;
    }
    cout << "Numbers generated!" << endl << endl;
    std::vector<uint64_t> v = numbers;
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {return a > b; });
    auto end = std::chrono::high_resolution_clock::now();
    cout << "Time to sort = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " milliseconds." << endl;
    bool check = issorted(numbers.begin(), numbers.end(), [](int a, int b) {return a > b; });
    if (!check) cout << "Wrong sort" << endl;
    else cout << "OK!" << endl;
    cout << endl;
    start = std::chrono::high_resolution_clock::now();
    parallelSort(8, v.begin(), v.end(), [](int a, int b) {return a > b; });
    end = std::chrono::high_resolution_clock::now();
    cout << "Time to parallel sort = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " milliseconds." << endl;
    check = issorted(v.begin(), v.end(), [](int a, int b) {return a > b; });
    if (!check) cout << "Wrong parallel sort" << endl;
    else cout << "OK!" << endl;

}