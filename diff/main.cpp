#include <iostream>
#include <optional>
#include <vector>
#include <fstream>

#include "src/diff_euler.hpp"

const int MAX_ITER_COUNT = 100000;

struct Point {
    double x;
    double y;

    Point& operator*=(double d) {
        x *= d;
        y *= d;
        return *this;
    }

    Point operator*(double d) const {
        return {x * d, y * d};
    }

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }

    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

};

Point operator*(double a, const Point& b) {
    return b * a;
}


Point solvePredatorPrey(
    double alpha, double beta,
    double delta, double gamma,
    Point p0, double t,
    double step, int maxIterCount = MAX_ITER_COUNT,
    int* iter = nullptr,
    std::vector<std::pair<double, Point>>* history = nullptr
) {
    auto F = [=](double t, Point p) -> std::optional<Point> {
        if (history) history->push_back({t, p});
        if (iter) *iter += 1;
        if (p.x <= 0 || p.y <= 0) return std::nullopt;
        return Point{(alpha - beta * p.y) * p.x, (delta * p.x - gamma) * p.y};
    };
    if (iter) *iter = 0;
    if (history) history->clear();
    return diffEuler1(0.0, p0, F, t, step, maxIterCount);
}

int main() {

    int iter;
    std::vector<std::pair<double, Point>> history;

    double alpha = 2.3;
    double beta = 0.1;
    double delta = 0.01;
    double gamma = 0.5;
    Point p0 = {50.001, 23.001};

    double l = 0;
    double r = 1.0;
    double eps = 1e-5;
    while (r - l > eps) {
        double m = (r + l) / 2;
        solvePredatorPrey(alpha, beta, delta, gamma, p0, MAX_ITER_COUNT, m, MAX_ITER_COUNT, &iter);
        if (iter < MAX_ITER_COUNT) {
            r = m;
        } else {
            l = m;
        }
    }

    auto [x, y] = solvePredatorPrey(alpha, beta, delta, gamma, p0, MAX_ITER_COUNT, l, MAX_ITER_COUNT, &iter, &history);

    {
        std::ofstream preyOut(RESOURCES_DIR "/prey.xy");
        std::ofstream predatorOut(RESOURCES_DIR "/predator.xy");
        for (auto [t, p]: history) {
            auto [x, y] = p;
            preyOut << std::fixed << t << " " << x << "\n";
            predatorOut << std::fixed << t << " " << y << "\n";
        }
    }

    std::cout << std::fixed << "dt=" << l << "\nx=" << x << "\ny=" << y << "\niterations=" << iter << std::endl;

    return 0;
}
