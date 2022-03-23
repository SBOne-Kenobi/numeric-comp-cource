#pragma once

#include <vector>
#include <stdexcept>

template<typename T>
T lagrangeInterpolation(T x, const std::vector<T>& px, const std::vector<T>& py, int degree) {
    if (px.size() != degree + 1 || py.size() != degree + 1) {
        throw std::logic_error("lagrangeInterpolation: mismatched number of points");
    }
    T result = 0;
    for (int i = 0; i <= degree; i++) {
        T prod = 1;
        for (int j = 0; j <= degree; j++) {
            if (i == j) continue;
            if (px[i] == px[j]) {
                throw std::logic_error("lagrangeInterpolation: expected different points");
            }
            prod *= (x - px[j]) / (px[i] - px[j]);
        }
        result += prod * py[i];
    }
    return result;
}