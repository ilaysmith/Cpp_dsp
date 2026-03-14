#include "Signal.h"

Signal downsample(const Signal &input, int factor) { // Принимаем значение input по ссылке, чтобы не создавать копию
    Signal result;
    result.fs = input.fs * factor; // Увеличиваем ЧД

    for (int i = 0; i < input.signal.size(); i += factor) // берём каждый factor отсчёт
    {
        result.signal.push_back(input.signal[i]); // Вставляем в конец каждый отсчёт + **1
    }

    return result;
}

//          ДОПОЛНИТЕЛЬНЫЕ КОММЕНТАРИИ
// **1 Можно использовать emplace_back() вместо push_back(). Первый метод вставляет элемент напрямую в память.
// Когда как второй (push_back) создаёт промежуточный объект перед добавлением в контейнер - копирует либо перемещает.
// Если передаём готовый объект - копирует, если созданный в моменте - перемещает.
// Так же у emplace_back() меньше нагрузка на аллокаторы new и delete/

