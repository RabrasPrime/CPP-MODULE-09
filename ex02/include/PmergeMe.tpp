//
// Created by tjooris on 1/28/26.
//

#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include <algorithm>
#include "PmergeMe.hpp"
#include <limits>

template <template<typename, typename> class Container>
Container<size_t, IndexAllocator> jacobsthalSequence(size_t n)
{
    Container<size_t, IndexAllocator> seq;

    if (n == 0)
        return seq;
    size_t j0 = 0;
    size_t j1 = 1;
    seq.push_back(j1);
    while (true)
    {
        size_t next = j1 + 2 * j0;
        if (next >= n)
            break;
        seq.push_back(next);
        j0 = j1;
        j1 = next;
    }
    return seq;
}

template <template<typename, typename> class Container>
Container<size_t, IndexAllocator> insertion_Order(size_t size)
{
    Container<size_t, IndexAllocator> order;
    Container<size_t, IndexAllocator> jacob = jacobsthalSequence<Container>(size);

    size_t lastInserted = 0;
    for (typename Container<size_t, IndexAllocator>::iterator it = jacob.begin();
         it != jacob.end(); ++it)
    {
        size_t jacobVal = *it;

        for (size_t i = jacobVal; i > lastInserted; --i)
        {
            if (i - 1 < size)
                order.push_back(i - 1);
        }
        lastInserted = jacobVal;
    }
    for (size_t i = lastInserted + 1; i <= size; ++i)
    {
        order.push_back(i - 1);
    }

    return order;
}

template <template<typename, typename> class Container>
void mergeInsertSort(Container<int, Allocator>& cont)
{
    size_t size = cont.size();
    int straggler = -1;

    if (size <= 1)
        return;

    Container<std::pair<int, int>, PairAllocator> pairs;
    bool hasStraggler = (size % 2 == 1);

    if (hasStraggler)
    {
        typename Container<int, Allocator>::iterator it = cont.begin();
        std::advance(it, size - 1);
        straggler = *it;
    }

    typename Container<int, Allocator>::iterator it = cont.begin();
    for (size_t i = 0; i < size / 2; ++i)
    {
        int a = *it++;
        int b = *it++;

        if (a > b)
            pairs.push_back(std::make_pair(a, b));
        else
            pairs.push_back(std::make_pair(b, a));
    }

    Container<int, Allocator> largerElements;
    for (typename Container<std::pair<int, int>, PairAllocator>::iterator pit = pairs.begin();
         pit != pairs.end(); ++pit)
    {
        largerElements.push_back(pit->first);
    }

    mergeInsertSort(largerElements);

    Container<std::pair<int, int>, PairAllocator> sortedPairs;
    Container<bool, std::allocator<bool> > used(pairs.size(), false);

    for (typename Container<int, Allocator>::iterator largeIt = largerElements.begin();
         largeIt != largerElements.end(); ++largeIt)
    {
        size_t idx = 0;
        for (typename Container<std::pair<int, int>, PairAllocator>::iterator pairIt = pairs.begin();
             pairIt != pairs.end(); ++pairIt, ++idx)
        {
            if (!used[idx] && pairIt->first == *largeIt)
            {
                sortedPairs.push_back(*pairIt);
                used[idx] = true;
                break;
            }
        }
    }
    Container<int, Allocator> mainChain;
    Container<int, Allocator> pend;

    for (typename Container<std::pair<int, int>, PairAllocator>::iterator sit = sortedPairs.begin();
         sit != sortedPairs.end(); ++sit)
    {
        mainChain.push_back(sit->first);
        pend.push_back(sit->second);
    }
    if (!pend.empty())
        mainChain.insert(mainChain.begin(), pend.front());
    Container<size_t, IndexAllocator> order = insertion_Order<Container>(pend.size());

    Container<bool, std::allocator<bool> > inserted(pend.size(), false);
    if (!pend.empty())
        inserted[0] = true;

    for (typename Container<size_t, IndexAllocator>::iterator orderIt = order.begin();
         orderIt != order.end(); ++orderIt)
    {
        size_t idx = *orderIt;

        if (idx >= pend.size() || inserted[idx])
            continue;

        typename Container<int, Allocator>::iterator pendIt = pend.begin();
        std::advance(pendIt, idx);

        int value = *pendIt;

        typename Container<int, Allocator>::iterator pos =
            std::lower_bound(mainChain.begin(), mainChain.end(), value);

        mainChain.insert(pos, value);
        inserted[idx] = true;
    }

    if (hasStraggler)
    {
        typename Container<int, Allocator>::iterator pos =
            std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }

    cont = mainChain;
}


#endif