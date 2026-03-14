
#include "Signal.h"
#include "AudioFile.h" // Для работы с wav и iqw

Signal load_wav_and_iqw() {

    Signal signal;
    AudioFile<float> audioFile;

    signal.fs = audioFile.getSampleRate(); // Получим ЧД

    int numSamples = audioFile.getNumSamplesPerChannel(); // Получим количество отсчётов в канале


    signal.signal.reserve(numSamples); // Выделим память для сигнала + **1
    for (int i = 0; i < numSamples; i++) {
        float I = audioFile.samples[0][i]; // Считаем с первого канала I-компоненты
        float Q = audioFile.samples[1][i]; // Считаем со второго канала Q-компоненты

        signal.signal.emplace_back(I, Q); // Вложим компоненты парами для комплексного числа + **2
    }
    return signal;
}

//              ДОПОЛНИТЕЛЬНЫЕ КОММЕНТАРИИ
// **1 Используем reverse, так как он просто выделит память, но не инициализирует
// **2 Можно использовать emplace_back() вместо push_back(). Первый метод вставляет элемент напрямую в память.
// Когда как второй (push_back) создаёт промежуточный объект перед добавлением в контейнер - копирует либо перемещает.
// Если передаём готовый объект - копирует, если созданный в моменте - перемещает.
// Так же у emplace_back() меньше нагрузка на аллокаторы new и delete/