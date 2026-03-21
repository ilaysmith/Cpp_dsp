clc ; clear all; close all

%% Чтение файла 
[y,Fs] = audioread('/home/morda/task_for_stc_1/Cpp_dsp/sound/21.281400_02.05.2023 15_00_38_USB.iqw');

%% Формирование огибающей
%signal = y(2:2:end).'; % SSB сигнал состоит либо из I либо из Q
signal = y(:,2); % SSB сигнал состоит либо из I либо из Q - Q USB

% нужно сместить сигнал на +1000 Гц
t = (0:length(signal)-1)'/Fs;
shift = 1000; % Гц
signal_shift = 1i*signal.*exp(1i*2*pi*shift*t);
eiler = exp(1i*2*pi*shift*t);

%% Фильтрация 

z = signal_shift - mean(signal_shift);

%% Нормирование

final = z / max(abs(z));

%% 
stereo_signal = [real(final), imag(final)];  % N x 2 матрица

%% Запись 
audiowrite('/home/morda/task_for_stc_1/Cpp_dsp/sound/USB_MATLAB_IQW.wav',stereo_signal,Fs);



%% Доп 
%% Фильтр скользящего среднего
%windowSize = 51;
%a = 1;
%b = (1/windowSize)*ones(1,windowSize);
%z = filter(b,a,audio);
