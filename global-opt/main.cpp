#include <iostream>
#include <cmath>
#include <random>

#include "src/random_search.hpp"
#include "src/lipo.hpp"
#include "src/genetic.hpp"

const double EPS = 1e-5;
const int MAX_ITER_COUNT = (int) 1e6;
const int POPULATION_SIZE = 1000;
const double MUTATION_PROB = 0.05;

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

    std::cout << std::fixed;

    std::default_random_engine engine(0);
    std::uniform_real_distribution<double> distribution(0, 1);

    auto gen = [&engine, &distribution]() {
        return distribution(engine);
    };

    const int iterations = 100;

    {
        engine.seed(0);
        std::cout << "Random search: " << std::endl;
        double avgCount = 0;
        double avgValue = 0;
        for (int i = 1; i <= iterations; i++) {
            int count;
            double value = randomSearch(-5., 5., rast, gen, EPS, MAX_ITER_COUNT, &count);
            avgValue += (value - avgValue) / i;
            avgCount += (count - avgCount) / i;
            std::cout << "-";
        }
        std::cout << "\n\tavgValue: " << avgValue << "\n\tavgCalls: " << avgCount << std::endl;
    }

    {
        engine.seed(0);
        std::cout << "LIPO search: " << std::endl;
        double avgCount = 0;
        double avgValue = 0;
        for (int i = 1; i <= iterations; i++) {
            int count;
            double value = lipoSearch(-5., 5., 73., rast, gen, EPS, MAX_ITER_COUNT, &count);
            avgValue += (value - avgValue) / i;
            avgCount += (count - avgCount) / i;
            std::cout << "-";
        }
        std::cout << "\n\tavgValue: " << avgValue << "\n\tavgCalls: " << avgCount << std::endl;
    }

    {
        engine.seed(0);
        std::cout << "Genetic search: " << std::endl;
        double avgCount = 0;
        double avgValue = 0;
        for (int i = 1; i <= iterations; i++) {
            int count;
            double value = geneticSearch(-5., 5., rast, gen, EPS, POPULATION_SIZE, MUTATION_PROB, MAX_ITER_COUNT, &count);
            avgValue += (value - avgValue) / i;
            avgCount += (count - avgCount) / i;
            std::cout << "-";
        }
        std::cout << "\n\tavgValue: " << avgValue << "\n\tavgCalls: " << avgCount << std::endl;
    }

    return 0;
}
