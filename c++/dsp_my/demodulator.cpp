#include "Signal.h"
#include <string>
#include <vector>
#include "Complex.h"
#include "Class_declarations.h"
#include <cmath> // У корня double иначе неявное преобразование

// 1. Демодулятор AM: комп огиб + вычис среднее + нормировка -> комп огиб в виде float?? А как сохранять его то?
Signal DemodulatorAM::getDemodulatedSignal(Signal signal) {

    std::vector<float> envelop; // Комплексная Огибающая

    for (size_t i = 0; i < signal.signal.size(); i++) {
        envelop.emplace_back(std::sqrt(pow(signal.signal[i].get_real(), 2) + pow(signal.signal[i].get_imag(), 2)));
    }

    filter filter;
    std::vector<float> result = filter.delete_const(envelop); // Вызов метода удаления постоянной составляющей

    // Нормировка
    size_t max = *std::max_element(result.begin(), result.end()); // Даёт указатель на максимальный элемент
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = result[i] / max;
    }


    return signal;
};


// 2. Демодулятор FM: комп сигнал + вычис фазы (сопряжение) + проход на проверку + нормировка -> Signal
Signal DemodulatorFM::getDemodulatedSignal(Signal signal) {

    return signal;
};


Demodulator *Factory::create(std::string type, int Fs) { // Возвращаем указатель
    if (type == "AM") {
        return new DemodulatorAM(Fs);        // Возвращаем указатель
    } else if (type == "FM") {
        return new DemodulatorFM(Fs);       // Возвращаем указатель
    }
    return nullptr;
}