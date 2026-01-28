//
// Created by tjooris on 1/28/26.
//

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

typedef std::allocator<int> Allocator;

template <template<typename, typename> class Container>
void    mergeInsertSort(Container<int, Allocator>& cont);

#include "PmergeMe.tpp"

#endif