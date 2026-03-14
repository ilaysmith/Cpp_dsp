#pragma once

#include <vector>
#include "Complex.h"

struct Signal {
    int fs;                        // ЧД
    std::vector<Complex<float>> signal; // вектор комплексных отсчётов
};