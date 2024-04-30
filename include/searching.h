#pragma once
#include "sorting.h"

unsigned linear_search(int const *const _array, unsigned const _length, int const _numberToSearch)
{
    for (unsigned index = 0; index < _length; ++index)
    {
        if (_array[index] == _numberToSearch)
            return index;
    }
    return -1;
}

//sorted array assumed
// indices have to be int for edge case checking
unsigned binary_search(int *const _array, int const _leftIndex, int const _rightIndex, int const _numberToSearch)
{
    int const middleIndex = (_leftIndex + _rightIndex) / 2;

    if (_array[middleIndex] == _numberToSearch)
        return middleIndex;

    if (_leftIndex >= _rightIndex)
        return -1;

    if (_numberToSearch < _array[middleIndex])
        return binary_search(_array, _leftIndex, middleIndex - 1, _numberToSearch);

    return binary_search(_array, middleIndex + 1, _rightIndex, _numberToSearch);
}