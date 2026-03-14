#include <vector>
#include "Class_declarations.h"


// Определение метода класса Фильтр
std::vector<float> filter::delete_const(std::vector<float> &signal) {
    float sum = 0.0;   // Для суммирования всех отсчётов
    std::vector<float> result; // Для сигнала без постоянной составляющей + **1
    result.reserve(signal.size()); // выделение памяти как под исходный сигнал

    for (int i = 0; i < signal.size(); i++) {
        sum += signal.at(i); // Сложение всех элементов. at() проверяет выход за границы + **2
    }
    float mean = sum / signal.size(); // Вычисление среднего

    for (int i = 0; i < signal.size(); i++) {
        float sample = signal.at(i); // Берём значение отсчёта
        result.push_back(sample - mean); // Вычитаем среднее из каждого отсчёта
    }

    return result;
}

//                  ДОПОЛНИТЕЛЬНЫЕ КОММЕНТАРИИ
// **1 при каждом push_back() может перераспределяться память по нескольку раз. То есть при добавлении нового элемента,
// старые копируются по новой - замедляется работа. Выделение памяти заранее помогает этого избежать (выделение 1 раз).
// **2 [] быстрее, так как не проверяет выход, но опаснее