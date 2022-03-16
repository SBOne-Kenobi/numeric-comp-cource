#pragma once

#include <cmath>

template<typename T, typename Func, typename Generator>
T randomSearch(T left, T right, Func func, Generator& g, T eps, int maxIterCount, int* callsCount = nullptr) {
    T point = g() * (right - left) + left;
    T value = func(point);
    if (callsCount) *callsCount = 1;
    for (int i = 0; i < maxIterCount; i++) {
        T rt = std::min(right, point + 1);
        T lt = std::max(left, point - 1);
        T nxt = g() * (rt - lt) + lt;
        T nxtValue = func(nxt);
        if (callsCount) ++(*callsCount);
        if (nxtValue < value) {
            T dv = value - nxtValue;
            value = nxtValue;
            point = nxt;
            if (dv < eps) break;
        }
    }
    return point;
}
