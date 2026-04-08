#ifndef DSP_MY_CLASS_DECLARATIONS_H
#define DSP_MY_CLASS_DECLARATIONS_H

#include "Signal.h"
#include <string>
#include <vector>
#include <iostream>
#include "AudioFile.h"
#include <fstream>
#include "any_function.h"
#include "Complex.h"
#include "Demodulator.h"
#include <memory>


// 1. Файловый Менеджер
class FileManager {
public:
    FileManager() = default;

    Signal loadSignal(const std::string &filename, Format format);

    void SaveSignal(const std::vector<float> &savedSignal, const std::string &fileName, Format format);

};

// 2. Фильтр скользящего среднего
class filter {
public:

    std::string type;

    filter() = default;

    filter(std::string type_filter) {
        type = type_filter;

    }

    std::vector<float> delete_const(std::vector<float> &data); // Метод удаления постоянной составляющей для АМ

    std::vector<float> delete_const_complex(Signal &signal); // Метод удаления постоянной составляющей для SSB
};


// 3. Демодулятор. Абстрактный класс
class Demodulator {
public:

    Demodulator() = default;

    int Fs;

    Demodulator(int fs) : Fs(fs) {};

    virtual ~Demodulator() = default;

    // сделать return vector<float> для АМ и Signal для FM
    virtual std::vector<float> getDemodulatedSignal(Signal signal) = 0; // указываем чистую виртуальную функцию + **1


};

// 4. Производный класс для АМ сигнала.
class DemodulatorAM : public Demodulator {
public:
    DemodulatorAM(int fs) : Demodulator(fs) {};

    std::vector<float> getDemodulatedSignal(Signal signal) override; // + **2
};

// 5. Производный класс для FM сигнала.
class DemodulatorFM : public Demodulator {
public:

    DemodulatorFM(int fs) : Demodulator(fs) {};

    std::vector<float> getDemodulatedSignal(Signal signal) override; // + **2
};

// 6. Производный класс для USB сигнала.
class DemodulatorUSB : public Demodulator {
public:

    DemodulatorUSB() = default;

    size_t currentSampleIndex;

    double currentTime;         // Текущее время в секундах

    DemodulatorUSB(int fs) : Demodulator(fs) {};

    std::vector<float> getDemodulatedSignal(Signal signal) override;

    Signal shift_USB(Signal signal); // Функция сдвига сигнала
};

// 7. Производный класс для LSB сигнала.
class DemodulatorLSB : public Demodulator {
public:

    DemodulatorLSB() = default;

    size_t currentSampleIndex; // Текущий отсчёт

    double currentTime;         // Текущее время в секундах

    DemodulatorLSB(int fs) : Demodulator(fs) {};

    std::vector<float> getDemodulatedSignal(Signal signal) override;

    Signal shift_LSB(Signal signal); // Функция сдвига сигнала
};

// 8. Класс паттерна "Абстрактная фабрика"
class Factory {
public:
    int Fs;

    std::unique_ptr<Demodulator> create_u(std::string type, int Fs); // Возвращает указатель с владением
    //Demodulator *create(std::string type, int Fs); // Метод создания демодулятора + **3

};

// 9. Класс фильтрации копмлексного сигнала
//class filter_complex

#endif //DSP_MY_CLASS_DECLARATIONS_H


//                          ДОПОЛНИТЕЛЬНЫЕ КОММЕНТАРИИ
// **1 Виртуальная функция - может быть переопределена (перегружена) в производном классе.
// Чистая виртуальная функция (=0) - не имеет определения в родительском классе, только в производных.
// **2 Явно указываем, что будем переопределять чистую виртуальную функцию (override)
// **3 Используем указатель. Demodulator - абстрактный класс (есть чисто виртуальная функция)
// - нельзя создать его объект. Только через указатель (ссылку) можно вызвать правильный виртуальный метод
// производного класса.
//
//
//