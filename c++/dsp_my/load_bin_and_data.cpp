#include "Signal.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream> // Для работы с файлом


Signal load_bin_and_data(const std::string &fileName, Signal &signal) {

    std::vector<float> bits;

    std::ifstream file(fileName, std::ios::binary); // Открываем файл на чтение
    if (!file.is_open()) {  // Проверка на открытие
        std::cout << "prob";
        // tellg() вернет -1
    }
    file.seekg(0, std::ios::end); // Перемещаемся в конец
    std::streamsize fileSize = file.tellg(); // Получаем размер в байтах + **1 + **2
    file.seekg(0, std::ios::beg); // Перемещаемся в начало

    bits.resize(fileSize / sizeof(float)); // Сколько чисел типа float помещается в файле


    file.read(reinterpret_cast<char *>(bits.data()), fileSize); // Читаем fileSize байт из файла и
    // пишем их в память с адреса bits.data() (указатель на первый элемент) + **3

    signal.signal.reserve(bits.size() / 2); // Резервируем память под signal + **4

    for (size_t i = 0;   // size_t так как размер вектора может оказаться большим
         i < bits.size(); i += 2) {
        signal.signal.emplace_back(bits[i], bits[i + 1]); // Создаём элементы, содержащие IQ + **5
    }
    file.close(); // Закрыть файл
    return signal;
}

//                ДОПОЛНИТЕЛЬНЫЕ КОММЕНТАРИИ
// **1 std::streamsize знаковый, целочисленный тип данных для работы с памятью. Его плюсы: явно указывает назначение
// переменной; большой диапазон значений для любой платформы.
// **2 tellg() функция, которая возвращает текущую позицию в файле.
// **3 Крайне важно использовать reinterpret_cast<char *>(bits.data():
// file.read() ожидает указатель на байт char*
// bits.data() возвращает float*
// Мы формально просим компилятор не обращать внимание на то, что это данные float (4 байта в каждом)
// и читать сырые байты по одному (как будто char*)
// **4 метод reserve просто зарезервирует место под новые элементы, не заполняя их. Например, resize их ещё и
// инициализирует
// **5 Можно использовать emplace_back() вместо push_back(). Первый метод вставляет элемент напрямую в память.
// Когда как второй (push_back) создаёт промежуточный объект перед добавлением в контейнер - копирует либо перемещает.
// Если передаём готовый объект - копирует, если созданный в моменте - перемещает.
// Так же у emplace_back() меньше нагрузка на аллокаторы new и delete/