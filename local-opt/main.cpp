#include <iostream>

#include <cassert>
#include "src/bisection.hpp"
#include "src/newton.hpp"

const double EPS = 1e-12;

double rast(double x) {
    return 10 + x * x - 10 * std::cos(2 * M_PI * x);
}

double dRast(double x) {
    return 2 * x + 20 * M_PI * std::sin(2 * M_PI * x);
}

double ddRast(double x) {
    return 2 + 40 * M_PI * M_PI * std::cos(2 * M_PI * x);
}

int main() {

    double x = bisectionSearch(-0.05, 0.02, EPS, dRast);
    assert(std::abs(x) < EPS);
    std::cout << "bisection 1 ok" << std::endl;
    x = newtonSearch(-0.05, dRast, ddRast, EPS);
    assert(std::abs(x) < EPS);
    std::cout << "newton 1 ok" << std::endl;

    return 0;
}
