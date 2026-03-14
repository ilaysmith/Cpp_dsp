#include "Signal.h"
#include <string>
#include <iostream>
#include <fstream> // Для работы с файлом


void save_bin_and_data(const Signal &signal, const std::string &filename) {
    std::ofstream file(filename, std::ios::binary); // Открыть файл на запись файла

    for (size_t i = 0; i < signal.signal.size(); i++) {
        float re = signal.signal[i].get_real(); // Сохраняем I-компоненты
        float im = signal.signal[i].get_imag(); // Сохраняем Q-компоненты

        file.write(reinterpret_cast<const char *>(&re), sizeof(float)); // **1 + **2
        file.write(reinterpret_cast<const char *>(&im), sizeof(float)); // **1 + **2
    }
    file.close(); // Закрыть файл
}

//              ДОПОЛНИТЕЛЬНЫЕ КОММЕНТАРИИ
// **1 Запись в файл из памяти с места &re количеством sizeof(float). Ведь файл хранит в себе float.
// **2 Крайне важно использовать reinterpret_cast<char *>(&re):
// file.read() ожидает указатель на байт char*
// bits.data() возвращает float*
// Мы формально просим компилятор не обращать внимание на то, что это данные float (4 байта в каждом)
// и читать сырые байты по одному (как будто char*)