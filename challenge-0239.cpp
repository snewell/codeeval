#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace
{
    std::vector<int> makeVector(std::string const &s)
    {
        std::istringstream is{s};
        std::vector<int> ret;
        int val;
        is >> val;
        while(is)
        {
            ret.push_back(val);
            is >> val;
        }
        return ret;
    }

    template <typename T>
    T partitionIter(T first, T last, bool back)
    {
        if(back)
        {
            auto pivot = *first;
            auto rLast = std::reverse_iterator<T>(first);
            auto ret = std::find_if(std::reverse_iterator<T>(last), rLast, [pivot] (int val) {
                return val < pivot;
            });
            if(ret != rLast)
            {
                std::iter_swap(first, ret);
            }
            return ret.base();
        }
        else
        {
            std::advance(last, -1);
            auto pivot = *last;
            auto ret = std::find_if(first, last, [pivot] (int val) {
                return val > pivot;
            });
            if(ret != last)
            {
                std::iter_swap(last, ret);
            }
            return ret;
        }
    }

    template <typename T>
    T partitionSort(T first, T last)
    {
        auto rFirst = first;
        auto rLast = last;
        auto back = true;
        while(first != last)
        {
            if(back)
            {
                last = partitionIter(first, last, back);
            }
            else
            {
                first = partitionIter(first, last, back);
            }
            back = !back;
        }
        return first;
    }

    template <typename T>
    unsigned int pivotSort(T first, T last)
    {
        auto distance = std::distance(first, last);
        if(distance > 1)
        {
            // The challenge requires a very specific order on each side of the pivot
            // point.  The disabled code should be valid but doesn't pass the CodeEval
            // input.
#if 0
            auto pivotVal = *first;
            auto pivot = std::partition(first, last, [pivotVal] (int val) {
                return val < pivotVal;
            });
#else
            auto pivot = partitionSort(first, last);
#endif
            auto next = pivot;
            std::advance(next, 1);
            return 1 + pivotSort(first, pivot) + pivotSort(next, last);
        }
        return 0;
    }

    unsigned int countPivots(std::vector<int> data)
    {
        return pivotSort(std::begin(data), std::end(data));
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    std::string line;

    std::getline(input, line);
    while(input)
    {
        auto data = makeVector(line);
        auto pivotCount = countPivots(std::move(data));
        std::cout << pivotCount << '\n';
        std::getline(input, line);
    }
    return 0;
}
