#pragma once

#include <cmath>

#include "point.hpp"

namespace {
    template<typename T>
    T batterwort(Point<T> p, Point<T> q, T sig) {
        T len2 = (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
        return 1 / (1 + len2 / (sig * sig));
    }

    template<typename T>
    void initWeights(Point<T>* ps, double* zs, T* w, T sig) {
        T mat[4][4];
        for (int i = 0; i < 4; i++) {
            mat[i][i] = 1;
            for (int j = i + 1; j < 4; j++) {
                mat[i][j] = mat[j][i] = batterwort(ps[i], ps[j], sig);
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = i; j < 4; j++) {
                T tmp = mat[j][i];
                if (tmp == 0) continue;
                for (int k = 0; k < 4; k++) {
                    mat[j][k] /= tmp;
                }
                zs[j] /= tmp;
                if (j == i) continue;
                for (int k = 0; k < 4; k++) {
                    mat[j][k] -= mat[i][k];
                }
                zs[j] -= zs[i];
            }
        }
        for (int i = 3; i >= 0; i--) {
            w[i] = zs[i];
            for (int j = 0; j < i; j++) {
                zs[j] -= mat[j][i] * w[i];
            }
        }
    }
}

template<typename T>
T radBasedInterpolation(Point<T>* ps, double* zs, Point<T> p, T sig = 1) {
    T w[4];
    initWeights(ps, zs, w, sig);
    T res = 0;
    for (int i = 0; i < 4; i++) {
        res += w[i] * batterwort(p, ps[i], sig);
    }
    return res;
}
