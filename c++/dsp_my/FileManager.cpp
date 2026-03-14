#include "Signal.h"
#include <string>
#include <iostream>
#include "AudioFile.h"
#include "any_function.h" // Необходимая библиотека для чтения wav и iqw
#include "Class_declarations.h"

void FileManager::SaveSignal(const Signal &saveSignal, const std::string &fileName, Format format) {

    AudioFile<float> audioFile;

    switch (format) {
        case Format::bin:
            save_bin_and_data(saveSignal, fileName); // Функция сохранения обработанного сигнала в расширении .bin
            break;

        case Format::dat:
            save_bin_and_data(saveSignal, fileName); // Функция сохранения обработанного сигнала в расширении .dat
            break;

        case Format::wav:
            save_wav_and_iqw(saveSignal, audioFile,
                             fileName); // Функция сохранения обработанного сигнала в расширении .wav
            break;

        case Format::iqw:
            save_wav_and_iqw(saveSignal, audioFile,
                             fileName);// Функция сохранения обработанного сигнала в расширении .iqw
            break;

        case Format::unknown:
            std::cout << "File unknown" << std::endl;
            break;
    }
}


Signal FileManager::loadSignal(const std::string &filename, Format format) {

    Signal signal;

    switch (format) {
        case Format::bin:
            signal = load_bin_and_data(filename, signal); // Функция извлечения байт из файла расширения .bin
            break;

        case Format::dat:
            signal = load_bin_and_data(filename, signal); // Функция извлечения байт из файла расширения .dat
            break;

        case Format::wav:

            signal = load_wav_and_iqw();    // Функция извлечения байт из файла расширения .wav
            break;

        case Format::iqw:

            signal = load_wav_and_iqw();    // Функция извлечения байт из файла расширения .iqw
            break;

        case Format::unknown:
            std::cout << "File unknown" << std::endl;
            break;
    }
    return signal;
}
