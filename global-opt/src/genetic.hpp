#pragma once

#include <cmath>
#include <climits>
#include <algorithm>

namespace {

    const unsigned int MAX = std::numeric_limits<unsigned int>::max();
    const unsigned int MAX_L = 8 * sizeof(unsigned int);

    unsigned int number_to_gray(unsigned int n) {
        return n ^ (n >> 1);
    }

    unsigned int gray_to_number(unsigned int g) {
        unsigned int n = 0;
        for (; g != 0; g >>= 1) { n ^= g; }
        return n;
    }

    template<typename T>
    unsigned int serialize(T left, T right, T value) {
        T t = (value - left) / (right - left);
        t *= MAX;
        return number_to_gray(t);
    }

    template<typename T>
    T deserialize(T left, T right, unsigned int value) {
        value = gray_to_number(value);
        T t = static_cast<T>(value) / static_cast<T>(MAX);
        return left + (right - left) * t;
    }

    template<typename T, typename Func>
    std::pair<unsigned int, T> selection(
        std::vector<std::pair<unsigned int, T>> &population,
        T left, T right, Func func,
        int populationSize,
        int *callsCount = nullptr
    ) {
        std::pair<unsigned int, T> minValue;
        for (int i = 0; i < populationSize * 3; i++) {
            population[i].second = func(deserialize(left, right, population[i].first));
            if (i == 0 || minValue.second > population[i].second) {
                minValue = population[i];
            }
            if (callsCount) ++(*callsCount);
        }
        std::nth_element(
            population.begin(),
            population.begin() + populationSize,
            population.end(),
            [](const std::pair<unsigned int, T> &a, const std::pair<unsigned int, T> &b) {
                return a.second < b.second;
            }
        );
        return minValue;
    }

    template<typename T, typename Generator>
    void generate(
        std::vector<std::pair<unsigned int, T>> &population,
        int populationSize, double mutationProb,
        Generator &g
    ) {
        for (int i = 0; i < populationSize; i++) {
            auto pos = static_cast<unsigned int>(g() * populationSize);
            for (int j = 0; j < 2; j++) {
                auto len = static_cast<unsigned int>(g() * MAX_L);
                unsigned int mask = MAX >> len;
                unsigned int newInst = mask & population[pos].first;
                newInst = newInst | ((~mask) & population[i].first);
                for (int k = 0; k < MAX_L; k++) {
                    if (g() < mutationProb) {
                        newInst = newInst ^ (1 << k);
                    }
                }
                population[i + j * populationSize].first = newInst;
            }
        }
    }

}

template<typename T, typename Func, typename Generator>
T geneticSearch(
    T left, T right, Func func,
    Generator &g, T eps,
    int populationSize,
    double mutationProb,
    int maxIterCount,
    int *callsCount = nullptr
) {
    if (callsCount) *callsCount = 0;
    std::vector<std::pair<unsigned int, T>> population(3 * populationSize);
    for (int i = 0; i < 3 * populationSize; i++) {
        population[i].first = serialize<T>(0, 1, g());
    }
    std::pair<unsigned int, T> minValue =
        selection(population, left, right, func, populationSize, callsCount);

    for (int i = 0; i < maxIterCount; i++) {
        generate(population, populationSize, mutationProb, g);
        T p = deserialize(left, right, minValue.first);
        T rt = std::min(right, p + 1);
        T lt = std::max(left, p - 1);
        for (int j = 2 * populationSize; j < 3 * populationSize; j++) {
            T nxt = g() * (rt - lt) + lt;
            population[j].first = serialize<T>(left, right, nxt);
        }
        std::pair<unsigned int, T> value =
            selection(population, left, right, func, populationSize, callsCount);
        if (std::abs(value.second - minValue.second) < eps) break;
        minValue = value;
    }
    return deserialize(left, right, minValue.first);
}
