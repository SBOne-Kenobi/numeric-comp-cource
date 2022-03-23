#include <iostream>
#include <iomanip>
#include <cmath>
#include "src/linear_int.hpp"
#include "src/lagrange_int.hpp"

int main() {
    std::cout << std::fixed << std::setprecision(10);
    double eps = 1e-7;
    double step = 2. * M_PI / 10.;

    std::vector<double> px = {
        0., step, 2 * step
    };
    std::vector<double> py = {
        0., std::sin(step), std::sin(2 * step)
    };
    while (true) {
        double x = 0.5 * step;
        double y = std::sin(x);
        double err1 = std::abs(linearInterpolation(x, 0., step, 0., std::sin(step)) - y);
        double err2 = std::abs(lagrangeInterpolation(x, px, py, 2) - y);
        if (std::abs(err1 - err2) < eps) {
            std::cout << "err linear: \t" << err1 <<
                        "\nerr lagrange: \t" << err2 <<
                        "\nstep: \t\t" << step << std::endl;
            break;
        }
        step *= 0.5;
    }

    return 0;
}
