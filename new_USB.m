clc ; clear all; close all

%% Чтение файла 
[y,Fs] = audioread('C:\Users\morda\Desktop\Signals\Task\21.281400_02.05.2023 15_00_38_USB.iqw');

%% Формирование огибающей
signal = y(2:2:end).'; % SSB сигнал состоит либо из I либо из Q

% нужно сместить сигнал на +1000 Гц
t = (0:length(signal)-1)'/Fs;
shift = 1000; % Гц
signal_shift = signal.*exp(1i*2*pi*shift*t);

%% Фильтрация 

z = signal - mean(signal);

%% Нормирование

final = z / max(abs(z));

%% Запись 
audiowrite('C:\Users\morda\Desktop\Signals\Task\new_USB.wav',final,Fs);



%% Доп 
%% Фильтр скользящего среднего
%windowSize = 51;
%a = 1;
%b = (1/windowSize)*ones(1,windowSize);
%z = filter(b,a,audio);