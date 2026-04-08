#include "Signal.h"
#include <string>
#include <vector>
#include "Complex.h"
#include "Class_declarations.h"
#include <cmath> // У корня double иначе неявное преобразование


Signal DemodulatorUSB::shift_USB(Signal signal) {
    // Сдвиг
    int shift = 1000; // Гц

    // Вектор времени
    double Ts = 1.0 / signal.fs; // Период дискретизации
    for (size_t i = 0; i < signal.signal.size(); i++) { // i - отсчёт
        //double t = i * Ts; // время, прошедшее с начала до i-го отчёта
        // currentTime для того, чтобы помнить в каком месте закончили работу с сигналом. Это поле классов SSB сигналов
        double t =
                currentTime + i * Ts; // время, прошедшее с начала до i-го отчёта. Здесь используется то, что учитываем
        // Комплексная экспонента + **3
        float angle = (2.0 * M_PI * shift * t);
        // Формула Эйлера
        Complex<float> eiler(std::cos(angle), std::sin(angle));
        // Смещённый сигнал
        Complex<float> shifted_bits = (signal.signal[i] * eiler);               // complex
        signal.signal[i] = shifted_bits;

    }
    return signal;
}
// Сохраняем currentTime , чтобы помнить, на какой части сигнала остановились. При первом запуске оно равно 0 и не влияет