#include <iostream>
#include "Signal.h"
#include "Class_declarations.h"
#include "any_function.h"
#include <memory>

int main() {

    //Signal signal;
    std::string fileName = "/home/morda/task_for_stc_1/Cpp_dsp/sound/7.133400_02.05.2023 14_57_07_LSB.iqw";
    // /home/morda/task_for_stc_1/dsp_my/dsp_my/AM3E_fs_24000_float_10_43_02.bin
    // /home/morda/task_for_stc_1/dsp_my/dsp_my/FM3E_fs_24000_float_12_16_56.bin"
    // /home/morda/task_for_stc_1/Cpp_dsp/sound/am_sound (1).dat
    // /home/morda/task_for_stc_1/Cpp_dsp/sound/7.133400_02.05.2023 14_57_07_LSB.iqw
    int Fs = 13000; // Из названия. Вообще 24000. Для dat 13000
    Format format = Format::iqw; // Из названия

    FileManager fileManager; // Объект класса файлового менеджера
    Signal signal(Fs);
    // Вызов метода получения данных из файла - Complex IQ. Тип данных float
    signal = fileManager.loadSignal(fileName, format);
    //signal.fs = ;


    Factory factory;
    std::unique_ptr<Demodulator> demod = factory.create_u("LSB", Fs); //+ **1
    //Demodulator *demod = factory.create("AM", Fs);

    std::vector<float> result = demod->getDemodulatedSignal(signal); // Вызовется DemodulatorAM::getDemodulatedSignal


    // Сохраним
    std::string new_file_name = "/home/morda/task_for_stc_1/dsp_my/dsp_my/AM3E_cpp.bin";

    fileManager.SaveSignal(result, new_file_name, Format::dat);
    //delete demod; // Возможна утечка памяти, если не вызвать delete (ранее был new)


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
// Комментарии
//std::unique_ptr<Demodulator> demod = factory.create_u("AM", Fs);
//указатель demod получает во владение область памяти типа Demodulator
// Нужен виртуальный деструктор для класса Demodulator, чтобы при удалении объекта через умный указатель корректно
// вызывался деструктор производного класса. Умный указатель хранит Demodulator* и при удалении вызывает деструктор
// Demodlator, а с вирутальным вызовет ещё и деструктор производного класса.
// std::make_unique<T>() - это функция, которая создаёт объект типа Т и возвращает std::unique<T>
// При выходе из области видимости указателя, объект удалится.
// У unique_ptr - у объекта один владелец. Так как его нельзя копировать, то используют std::move - его перемещают.
// new = std::move(old_unique); - передали владение. старый указатель автоматически nullptr
// Можно использовать вектор владельцев для поочередного вызова всех методов. Передача происходит тем, что move преобра
// - зует УУ во временную ссылку

//std::vector<std::unique_ptr<Demodulator>> demods;
//demods.push_back(factory.create("AM", Fs));      // Перемещение
//demods.push_back(factory.create("FM", Fs));
//demods.push_back(factory.create("LSB", Fs));

// Использование
//for (auto& d : demods) {
//auto result = d->getDemodulatedSignal(signal);
//}

// Можно так более простой пример
// auto iPtr = std::make_unique<int>(42);     // Указатель на int со значением 42. Выделить память под 42 инта и указать на них


// shared_ptr - несколько владельцев + нагружает, так как есть счётчик ссылок. Когда все ссылки в 0, то объект удалится
//
