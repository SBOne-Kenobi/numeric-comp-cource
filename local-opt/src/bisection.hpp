#pragma once

#include <stdexcept>
#include <cmath>
#include <functional>

#include "utils.hpp"

template<typename T, typename Func>
T bisectionSearch(T lowerBorder, T upperBorder, T eps, Func func) {
    T lowerValue = func(lowerBorder);
    T upperValue = func(upperBorder);
    if (!checkDiffSigns(lowerValue, upperValue)) {
        throw std::invalid_argument("BisectionSearch: function values must be different signs");
    }
    while (upperBorder - lowerBorder > eps) {
        T mid = lowerBorder + (upperBorder - lowerBorder) / 2;
        T midValue = func(mid);
        if (midValue == 0) {
            return mid;
        }
        if (checkDiffSigns(lowerValue, midValue)) {
            upperBorder = std::move(mid);
        } else {
            lowerBorder = std::move(mid);
            lowerValue = std::move(midValue);
        }
    }
    return lowerBorder;
}
