#include "Signal.h"
#include "AudioFile.h" // Для работы с wav и iqw

void save_wav_and_iqw(const Signal &saveSignal, AudioFile<float> audioFile, const std::string &fileName) {

    audioFile.setSampleRate(int(saveSignal.fs)); // Получаем ЧД
    audioFile.setBitDepth(32); // Получаем сколько бит на 1 отсчёт + **1

    size_t numSamples = saveSignal.signal.size(); // Количество комплексных отсчётов в сигнале saveSignal.signal
    audioFile.setAudioBufferSize(2, numSamples); // Выделяем память для аудиобуфера + **2

    for (size_t i = 0; i < numSamples; ++i) {
        audioFile.samples[0][i] = saveSignal.signal[i].get_real(); // Первый канал I (массив)
        audioFile.samples[1][i] = saveSignal.signal[i].get_imag(); // Второй канал Q (массив)
    }
    audioFile.save(fileName, AudioFileFormat::Wave);
}

//              ДОПОЛНИТЕЛЬНЫЕ КОММЕНТАРИИ
// **1 Это разрядность (глубина кодирования). Так как работаем с float, сохраняем в 32-битном формате
// **2 2 - два канала (стерео), numSamples - количество сэмплов на канал
