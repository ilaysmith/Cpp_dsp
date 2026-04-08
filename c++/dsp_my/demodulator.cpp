#include "Signal.h"
#include <string>
#include <vector>
#include "Complex.h"
#include "Class_declarations.h"
#include <cmath> // У корня double иначе неявное преобразование

// 1. Демодулятор AM: комплексная огибающая + фильтрация средним значением + нормировка
std::vector<float> DemodulatorAM::getDemodulatedSignal(Signal signal) {

    std::vector<float> envelop; // Комплексная Огибающая

    for (size_t i = 0; i < signal.signal.size(); i++) {
        envelop.emplace_back(std::sqrt(pow(signal.signal[i].get_real(), 2) + pow(signal.signal[i].get_imag(), 2)));
    }

    // Фильтрация
    filter filter;
    std::vector<float> result = filter.delete_const(envelop); // Вызов метода удаления постоянной составляющей

    // Нормировка

    size_t max = *std::max_element(result.begin(), result.end()); // Даёт указатель на максимальный элемент
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = result[i] / max;
    }


    // Необязательно? На выходе пусть и будет вектор float??
    Signal out;
    out.signal.reserve(result.size() / 2);
    for (size_t i = 0;   // size_t так как размер вектора может оказаться большим
         i < result.size(); i += 2) {
        out.signal.emplace_back(result[i], result[i + 1]); // Создаём элементы, содержащие IQ + **5
    }

    return result;
};


// 2. Демодулятор FM: комп сигнал + вычисление фазы (сопряжение) + проход на проверку + нормировка
std::vector<float> DemodulatorFM::getDemodulatedSignal(Signal signal) {
    // Комплексный сигнал уже на входе

    std::vector<float> audio;
    audio.resize(signal.signal.size()); // **1 + **2
    // Частное двух комплексных отсчётов (произведение на комплексно сопряжённый). Фаза между ними
    for (size_t i = 0; i < signal.signal.size() - 1; i++) {
        audio[i] = (signal.signal[i].conjugate() * signal.signal[i + 1]).phase();
    }

    return audio;
};

// 3. Демодулятор USB: Q компоненты комплексной огибающей + перенос + фильтрация + нормировка
std::vector<float> DemodulatorUSB::getDemodulatedSignal(Signal signal) {         // complex

    // Сдвиг
    shift_USB(signal);

    // Берём одну составляющую
    std::vector<float> valid_signal;
    valid_signal.resize(signal.signal.size() * 2);

    for (size_t i = 0; i < signal.signal.size(); i++) {
        valid_signal[i] = signal.signal[i].get_imag();
    }

    // Фильтрация
    filter Filter;
    Filter.delete_const(valid_signal);


    // Нормировка
    size_t max = *std::max_element(valid_signal.begin(), valid_signal.end()); // Даёт указатель на максимальный элемент
    for (size_t i = 0; i < valid_signal.size(); i++) {
        valid_signal[i] = valid_signal[i] / max;
    }

    // Обновляем состояние после обработки
    currentSampleIndex += valid_signal.size();
    currentTime = currentSampleIndex * (1.0 / Fs);

    return valid_signal;
}

// 4. Демодулятор SSB: I компоненты комплексной огибающей + перенос + фильтрация + нормировка
std::vector<float> DemodulatorLSB::getDemodulatedSignal(Signal signal) {

    // Сдвиг
    shift_LSB(signal);

    // Берём составляющую
    std::vector<float> valid_signal;
    valid_signal.resize(signal.signal.size() * 2);
    for (size_t i = 0; i < signal.signal.size(); i++) {
        valid_signal[i] = signal.signal[i].get_imag();
    }

    // Фильтрация
    filter Filter;
    Filter.delete_const(valid_signal); // действительный сигнал

    // Нормировка
    size_t max = *std::max_element(valid_signal.begin(), valid_signal.end()); // Даёт указатель на максимальный элемент
    for (size_t i = 0; i < valid_signal.size(); i++) {
        valid_signal[i] = valid_signal[i] / max;
    }

    // Обновляем состояние после обработки. Если сигнал был не полностью обработан, то здесь это будет учтено и использовано при следующем запуске
    currentSampleIndex += valid_signal.size();
    currentTime = currentSampleIndex * (1.0 / Fs);

    return valid_signal;
}

// 5. Фабрика
std::unique_ptr<Demodulator> Factory::create_u(std::string type, int Fs) {
    if (type == "AM") {
        return std::make_unique<DemodulatorAM>(Fs); // Возвращаем указатель
    } else if (type == "FM") {
        return std::make_unique<DemodulatorFM>(Fs); // Возвращаем указатель
    } else if (type == "USB") {
        return std::make_unique<DemodulatorUSB>(Fs); // Возвращаем указатель
    } else if (type == "LSB") {
        return std::make_unique<DemodulatorLSB>(Fs); // Возвращаем указатель
    }
    return nullptr;
}

//Demodulator *Factory::create(std::string type, int Fs) { // Возвращаем указатель
//    if (type == "AM") {
//       return new DemodulatorAM(Fs);        // Возвращаем указатель
// } else if (type == "FM") {
//   return new DemodulatorFM(Fs);       // Возвращаем указатель
//  } else if (type == "USB") {
//     return new DemodulatorUSB(Fs);
// } else if (type == "LSB") {
//    return new DemodulatorLSB(Fs);
//}
//return nullptr;
//}

//          ДОПОЛНИТЕЛЬНЫЕ КОММЕНТАРИИ
// **1 - Использовал вместо resize (Выделяет память и заполняет нулями) метод reserve (просто резервирует память).
//      Получилось так, что я не создал объект audio, а просто выделил под него память.
//      После reserve() нельзя использовать [i]. Нужно использовать push_back() или emplace_back()
// **2 - После resize() использовать emplace_back() или push_back() не правильно. Биты будут вставлять в то место, которое
//       находится после выделенной памяти.
// **3 - Использовать комплексную экспоненту в виде exp^(2*pi*Shift*t) не имеет смысла, так как она возвращает просто
//       число 2,7 в какойто степени.
//       Нужно разложить по формуле Эйлера.
//       Либо можно использовать перегрузку std::exp() в std::complex, но у меня используется свой Complex.h.
//       И в нём такого нет.


// Нормировка для комплексного сигнала
/*
float max_mag = 0.0f;
for (size_t i = 0; i < signal.signal.size(); i++) {
float mag = signal.signal[i].magnitude();
if (mag > max_mag) {
max_mag = mag;
}
}
 */