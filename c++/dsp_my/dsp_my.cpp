#include <iostream>
#include "Signal.h"
#include "Class_declarations.h"
#include "any_function.h"


int main() {

    //Signal signal;
    std::string fileName = "/home/morda/task_for_stc_1/dsp_my/dsp_my/AM3E_fs_24000_float_10_43_02.bin";
    int Fs = 24000; // Из названия
    Format format = Format::bin; // Из названия

    FileManager fileManager; // Объект класса файлового менеджера
    Signal signal;
    // Вызов метода получения данных из файла - Complex IQ. Тип данных float
    signal = fileManager.loadSignal(fileName, format);


    Factory factory;
    Demodulator *demod = factory.create("AM", Fs);

    Signal result = demod->getDemodulatedSignal(signal); // Вызовется DemodulatorAM::getDemodulatedSignal

    // Сохраним
    std::string new_file_name = "/home/morda/task_for_stc_1/dsp_my/dsp_my/AM3E_cpp.bin";
    fileManager.SaveSignal(result, new_file_name, Format::bin);
    delete demod; // Возможна утечка памяти, если не вызвать delete (ранее был new)


    // ДЛЯ FM save можно для Signal
    // ДЛЯ AM save как для комп огиб, но это не Signal уже (std::vector<float> ?? )



    //FileManager File;
    //File.loadSignal(FileName);

    //Factory factory;
    //factory.create("AM", Fs);

    //std::string out_name = "Out_file";
    //Signal<double> savesignal;
    //File.SaveSignal(savesignal, out_name, format);

    //std::cout << "Hello World!\n";
}
