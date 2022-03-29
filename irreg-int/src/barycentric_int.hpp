#pragma once

#include "point.hpp"

template<typename T>
T barycentricInterpolation(Point<T> p0, Point<T> p1, Point<T> p2, T z0, T z1, T z2, Point<T> p) {
    T d = (p1.y - p2.y) * (p0.x - p2.x) + (p2.x - p1.x) * (p0.y - p2.y);
    T t0 = ((p1.y - p2.y) * (p.x - p2.x) + (p2.x - p1.x) * (p.y - p2.y)) / d;
    T t1 = ((p2.y - p0.y) * (p.x - p2.x) + (p0.x - p2.x) * (p.y - p2.y)) / d;
    T t2 = 1 - t0 - t1;
    return z0 * t0 + z1 * t1 + z2 * t2;
}
