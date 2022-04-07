#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <tuple>

#include "src/newton_cotes.hpp"
#include "src/legendre_gauss.hpp"

const double EPS = 1e-5;

auto getDOwen(double h) {
    return [=](double x) -> double {
        return std::exp(-0.5 * h * h * (1 + x * x)) / (1 + x * x);
    };
}

auto getOwenNewtonCotes(int n) {
    return [=](double h, double a) -> double {
        auto dOwen = getDOwen(h);
        return integralNewtonCotes(0., a, n, dOwen) / (2 * M_PI);
    };
}

auto getOwenLegendreGauss(int n) {
    return [=](double h, double a) -> double {
        auto dOwen = getDOwen(h);
        return integralLegendreGauss(0., a, n, dOwen) / (2 * M_PI);
    };
}

int main() {

    std::vector<std::tuple<double, double, double>> tests{
    //   h      a       expected
        {1,     1,      0.0667418},
        {0.3,   2,      0.162604},
        {2.3,   0.5,    0.00433422},
        {0.1,   3.1,    0.197896}
    };

    auto owenNewtonCotes = getOwenNewtonCotes(10);
    for (auto [h, a, expected] : tests) {
        assert(std::abs(owenNewtonCotes(h, a) - expected) < EPS);
    }

    auto owenLegendreGauss = getOwenLegendreGauss(10);
    for (auto [h, a, expected] : tests) {
        assert(std::abs(owenLegendreGauss(h, a) - expected) < EPS);
    }

    std::cout << "Seems ok!" << std::endl;

    return 0;
}
