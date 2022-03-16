#pragma once

#include <cmath>

template<typename T, typename Func, typename Generator>
T lipoSearch(T left, T right, T L, Func func, Generator& g, T eps, int maxIterCount, int* callsCount = nullptr) {
    T point = g() * (right - left) + left;
    T value = func(point);
    std::vector<T> points = {point};
    std::vector<T> values = {value};
    if (callsCount) *callsCount = 1;
    for (int i = 0; i < maxIterCount; i++) {
        T rt = std::min(right, point + 1);
        T lt = std::max(left, point - 1);
        T nxt = g() * (rt - lt) + lt;

        T estimate = value - L * std::abs(point - nxt);
        for (int j = 0; j < points.size(); j++) {
            estimate = std::max(estimate, values[j] - L * std::abs(points[j] - nxt));
        }
        if (estimate > value) continue;

        T nxtValue = func(nxt);
        if (callsCount) ++(*callsCount);
        points.push_back(nxt);
        values.push_back(nxtValue);
        if (nxtValue < value) {
            T dv = value - nxtValue;
            value = nxtValue;
            point = nxt;
            if (dv < eps) break;
        }
    }
    return point;
}

