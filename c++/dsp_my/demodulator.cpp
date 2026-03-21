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

    // Проход по значениям
    for (size_t i; i < audio.size(); i++) {
        if (audio[i] > M_PI) {
            audio[i] = audio[i] - 2 * M_PI;
        }
        if (audio[i] < -M_PI) {
            audio[i] = audio[i] + 2 * M_PI;
        }
    }

    // Нормировка
    float max = *std::max_element(audio.begin(), audio.end());
    for (size_t i = 0; i < audio.size(); i++) {
        audio[i] = audio[i] / max;
    }
    return audio;
};

// 3. Демодулятор USB: Q компоненты комплексной огибающей + перенос + фильтрация + нормировка
std::vector<float> DemodulatorUSB::getDemodulatedSignal(Signal signal) {

    // Сдвиг
    int shift = 1000; // Гц
    std::vector<float> result;
    result.resize(signal.signal.size() * 2);

    for (size_t i = 0; i < signal.signal.size(); i++) {
        signal.signal[i].set_real(0);
    }

    // Вектор времени
    double Ts = 1.0 / signal.fs; // Период дискретизации
    for (size_t i = 0; i < signal.signal.size(); i++) { // i - отсчёт
        double t = i * Ts; // время, прошедшее с начала до i-го отчёта

        // Комплексная экспонента + **3
        float angle = (2.0 * M_PI * shift * t);
        // Формула Эйлера
        Complex<float> eiler(std::cos(angle), std::sin(angle));
        // Смещённый сигнал
        Complex<float> shifted_bits = (signal.signal[i] * eiler);
        signal.signal[i] = shifted_bits;

        //result[2 * i] = shifted_bits.get_real();
        //result[2 * i + 1] = shifted_bits.get_imag();

    }

    // Фильтрация
    filter Filter;
    Filter.delete_const_complex(signal);


    // Нормировка. Найдём максимальное значение по модулю
    float max_mag = 0.0f;
    for (size_t i = 0; i < signal.signal.size(); i++) {
        float mag = signal.signal[i].magnitude();
        if (mag > max_mag) {
            max_mag = mag;
        }
    }

    for (size_t i = 0; i < signal.signal.size(); i++) {
        signal.signal[i] = signal.signal[i] * (1 / max_mag);
    }
    // Переход к вектору
    for (size_t i = 0; i < signal.signal.size(); i++) {
        result[2 * i] = signal.signal[i].get_real();
        result[2 * i + 1] = signal.signal[i].get_imag();
    }

    return result;
}

// 4. Демодулятор SSB: I компоненты комплексной огибающей + перенос + фильтрация + нормировка
std::vector<float> DemodulatorLSB::getDemodulatedSignal(Signal signal) {

    // Сдвиг
    int shift = 1000; // Гц
    std::vector<float> result;
    result.resize(signal.signal.size() * 2);

    for (size_t i = 0; i < signal.signal.size(); i++) {
        signal.signal[i].set_real(0);
    }

    // Вектор времени
    double Ts = 1.0 / signal.fs; // Период дискретизации
    for (size_t i = 0; i < signal.signal.size(); i++) { // i - отсчёт
        double t = i * Ts; // время, прошедшее с начала до i-го отчёта

        // Комплексная экспонента + **3
        float angle = (2.0 * M_PI * shift * t);
        // Формула Эйлера
        Complex<float> eiler(std::cos(angle), std::sin(angle));
        // Смещённый сигнал
        Complex<float> shifted_bits = (signal.signal[i] * eiler);
        signal.signal[i] = shifted_bits;

        //result[2 * i] = shifted_bits.get_real();
        //result[2 * i + 1] = shifted_bits.get_imag();

    }

    // Фильтрация
    filter Filter;
    Filter.delete_const_complex(signal);


    // Нормировка. Найдём максимальное значение по модулю
    float max_mag = 0.0f;
    for (size_t i = 0; i < signal.signal.size(); i++) {
        float mag = signal.signal[i].magnitude();
        if (mag > max_mag) {
            max_mag = mag;
        }
    }

    for (size_t i = 0; i < signal.signal.size(); i++) {
        signal.signal[i] = signal.signal[i] * (1 / max_mag);
    }
    // Переход к вектору
    for (size_t i = 0; i < signal.signal.size(); i++) {
        result[2 * i] = signal.signal[i].get_real();
        result[2 * i + 1] = signal.signal[i].get_imag();
    }

    return result;
}

// 5. Фабрика
Demodulator *Factory::create(std::string type, int Fs) { // Возвращаем указатель
    if (type == "AM") {
        return new DemodulatorAM(Fs);        // Возвращаем указатель
    } else if (type == "FM") {
        return new DemodulatorFM(Fs);       // Возвращаем указатель
    } else if (type == "USB") {
        return new DemodulatorUSB(Fs);
    } else if (type == "LSB") {
        return new DemodulatorLSB(Fs);
    }
    return nullptr;
}

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