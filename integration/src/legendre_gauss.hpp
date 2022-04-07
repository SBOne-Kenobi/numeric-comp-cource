#pragma once

#include "abscissa.hpp"
#include "weights.hpp"

template<typename T, typename Func>
T integralLegendreGauss(T a, T b, int n, Func func) {
    T result = 0;
    for (int i = 0; i < n; i++) {
        T x = abscissa[n - 2][i] * (b - a) / 2 + (b + a) / 2;
        result += func(x) * weights[n - 2][i];
    }
    return result * (b - a) / 2;
}
