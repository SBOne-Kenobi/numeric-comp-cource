#pragma once

template<typename T, typename Func>
T newtonSearch(T x0, Func func, Func dFunc, T eps, int maxIter = 100000) {
    for (int i = 0; i < maxIter; i++) {
        T dx = func(x0) / dFunc(x0);
        x0 -= dx;
        if (std::abs(dx) < eps)
            break;
    }
    return x0;
}
