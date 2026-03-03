clc ; clear all; close all

%% Чтение файла 
[y,Fs] = audioread('C:\Users\morda\Desktop\Signals\Task\7.133400_02.05.2023 14_57_07_LSB.iqw');

%% Формирование огибающей
signal = y(1:2:end).'; % SSB сигнал состоит либо из I либо из Q

% нужно сместить сигнал на -1000 Гц, так как на 0 Гц должна была бы быть
% постоянная составляющая
t = (0:length(signal)-1)'/Fs;
shift = -1000; % Гц
signal_shift = real(signal.*exp(1i*2*pi*shift*t));
%% Фильтрация 

z = signal_shift - mean(signal_shift);

%% Нормирование

final = z / max(abs(z));

%% Запись 
audiowrite('C:\Users\morda\Desktop\Signals\Task\new_LSB.wav',final,Fs);