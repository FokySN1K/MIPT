#include <functional>
#include <deque>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdint>
using std::cout, std::endl, std::size_t;
using namespace std::chrono_literals;

template <typename RandIt>
RandIt getMaxV(const std::vector<RandIt>& v)
{
    RandIt result = v.at(0);
    for (auto el : v)
    {
        if (*el > *result)
            result = el;
    }
    return result;
}

template <typename RandIt>
RandIt getMax(RandIt start, RandIt finish)
{
    RandIt maxIt = start;
    for (auto it = start; it != finish; ++it)
    {
        if (*it > *maxIt)
            maxIt = it;
    }
    return maxIt;
}

template <typename RandIt>
void getMaxOne(RandIt first, RandIt last, RandIt& result)
{
    result = first;
    for (++first; first != last; ++first)
    {
        if (*first > *result)
        {
            result = first;
        }
    }
}

template <typename RandIt>
RandIt getMaxPar(int n, RandIt start, RandIt finish)
{
    unsigned long const length = finish - start;

    unsigned long block_size = length;
    if (n == 0)
    {
        unsigned long const hardware_threads = std::thread::hardware_concurrency();
        n = (hardware_threads != 0 ? hardware_threads : 2);
    }

    block_size /= n;
    std::vector<RandIt> results(n);
    std::vector<std::thread> threads(n - 1);
    RandIt block_start = start;

    for (unsigned long i = 0; i < (n - 1); ++i)
    {
        RandIt block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(getMaxOne<RandIt>, block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    getMaxOne(block_start, finish, results[n - 1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return getMaxV(results);
}

int main()
{

    cout << "Generating numbers!" << endl;
    std::deque<uint64_t> numbers;
    numbers.push_back(777);
    for (size_t i = 1; i < 1e7; ++i)
    {
        numbers.push_back(numbers.back() * i + 1);
    }
    cout << "Numbers generated!" << endl;

    auto start = std::chrono::high_resolution_clock::now();
    auto it = getMax(numbers.begin(), numbers.end());
    auto end = std::chrono::high_resolution_clock::now();
    cout << "Maximum = " << *it << endl;
    cout << "Time to calclulate max = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " milliseconds." << endl;

    start = std::chrono::high_resolution_clock::now();
    it = getMaxPar(0, numbers.begin(), numbers.end());
    end = std::chrono::high_resolution_clock::now();
    cout << "Maximum = " << *it << endl;
    cout << "Time to calclulate max = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " milliseconds." << endl;

    return 0;
}