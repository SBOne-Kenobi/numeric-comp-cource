#pragma once

template<typename T, typename Func>
T integralNewtonCotes(T a, T b, int n, Func func) {
    n -= 1;
    T h = (b - a) / n;
    T dx = h / 3;
    T result = 0;
    T predF = func(a);
    for (int i = 1; i <= n; i++) {
        T predX = a + (i - 1) * h;
        T curF = func(a + i * h);
        T tmp = predF + 3 * (func(predX + dx) + func(predX + 2 * dx)) + curF;
        tmp *= ((dx * 3) / 8);
        result += tmp;
        predF = curF;
    }
    return result;
}
