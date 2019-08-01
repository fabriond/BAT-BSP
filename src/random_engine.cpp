#include <random>
#include <iostream>
#include <time.h>
#include "../include/random_engine.h"

static std::default_random_engine generator(time(0));

double uniformRandom(double min, double max) {
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

int uniformRandom(int min, int max){
    std::cout << "test" << std::endl;
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

double normalRandom(double mean, double sd) {
    std::normal_distribution<double> distribution(mean, sd);
    return distribution(generator);
}