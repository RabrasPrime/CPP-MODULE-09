//
// Created by tjooris on 1/28/26.
//

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <memory>
#include <utility>
#include <cstddef>

typedef std::allocator<int> Allocator;
typedef std::allocator<std::pair<int, int> > PairAllocator;
typedef std::allocator<size_t> IndexAllocator;

template <template<typename, typename> class Container>
void    mergeInsertSort(Container<int, Allocator>& cont);

#include "PmergeMe.tpp"

#endif