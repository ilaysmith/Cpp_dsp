clc; clear all; close all
%% Чтение файла
fid = fopen('C:\Users\morda\Desktop\Signals\Task\file1EuropaPlus (1).bin');
y = fread(fid,inf,"single");
fclose(fid);
Fs = 500000; % 500 МГц 

%% Формирование I Q компонент

I = y(1:2:end);
Q = y(2:2:end);

comp_signal = I +1i*Q;

for i = 1:(length(comp_signal) - 1)
    audio(i) = angle((comp_signal(i+1))*conj((comp_signal(i))));
end

audio = audio.';

%% Фильтрация 

% не требуется, потому что её нет

%% Фильтр скользящего среднего
windowSize = 51;
a = 1;
b = (1/windowSize)*ones(1,windowSize);
z = filter(b,a,audio);

%% Формирование сигнала из I Q компонент 

%% Нормируем
z_norm = z / abs(max(z));

%% Запись сигнала 
audiowrite('C:\Users\morda\Desktop\Signals\Task\new_file1EuropaPlus.wav',z_norm,Fs);
