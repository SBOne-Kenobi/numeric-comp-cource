#pragma once

template<typename T>
bool checkDiffSigns(T a, T b) {
    return (a > 0 && b < 0) || (a < 0 && b > 0);
}
