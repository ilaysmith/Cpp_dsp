#pragma once

#include <vector>
#include "Complex.h"

struct Signal {
    Signal(int fs) {};

    Signal() = default;

    int fs;                        // ЧД
    std::vector<Complex<float>> signal; // вектор комплексных отсчётов
};