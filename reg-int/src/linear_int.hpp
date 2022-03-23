#pragma once

#include <stdexcept>

template<typename T>
T linearInterpolation(T x, T x0, T x1, T y0, T y1) {
    if (x0 == x1) {
        throw std::logic_error("linearInterpolation: expected different points");
    }
    x = (x - x0) / (x1 - x0);
    return y0 * (1 - x) + y1 * x;
}
