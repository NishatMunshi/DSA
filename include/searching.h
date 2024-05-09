#pragma once

#include "sorting.h"

size_t linear_search(int const *const _array, size_t const _length, int const _numberToSearch)
{
    for (size_t index = 0; index < _length; ++index)
    {
        if (_array[index] == _numberToSearch)
            return index;
    }
    return SIZE_MAX;
}

// sorted array assumed
size_t binary_search(int const *const _array, size_t const _leftIndex, size_t const _rightIndex, int const _numberToSearch)
{
    size_t const middleIndex = (_leftIndex + _rightIndex) / 2;

    if (_array[middleIndex] == _numberToSearch)
    {
        return middleIndex;
    }

    if (_numberToSearch < _array[middleIndex] && middleIndex > _leftIndex)
    {
        return binary_search(_array, _leftIndex, middleIndex - 1, _numberToSearch);
    }
    else if (_numberToSearch > _array[middleIndex] && middleIndex < _rightIndex)
    {
        return binary_search(_array, middleIndex + 1, _rightIndex, _numberToSearch);
    }
    return SIZE_MAX;
}