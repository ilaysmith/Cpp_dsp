#ifndef DSP_MY_ANY_FUNCTION_H
#define DSP_MY_ANY_FUNCTION_H

#include <string>
#include "Signal.h"
#include "AudioFile.h" // Для работы с wav и iqw

// Класс перечисления
enum class Format {
    bin,
    dat,
    wav,
    iqw,
    unknown
};

// Объявления функций, не являющихся методами классов (но используемые там)
Signal load_bin_and_data(const std::string &fileName, Signal &signal);

Signal load_wav_and_iqw();

void save_wav_and_iqw(const Signal &saveSignal, AudioFile<float> audioFile, const std::string &fileName);

void save_bin_and_data(const Signal &signal, const std::string &filename);

#endif //DSP_MY_ANY_FUNCTION_H
