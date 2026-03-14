clear all; close all; clc;

%% Чтение файла 
% Содержит просто данные: читаем через fread

fid = fopen('/home/morda/task_for_stc_1/Cpp_dsp/sound/AM3E_bin.bin');
y = fread(fid, inf, 'single'); % в матлаб аналог float это single 
Fs = 24000; % задана в названии
% получили отсчёты комплексного сигнала

%% Запись сигнала
audiowrite('/home/morda/task_for_stc_1/Cpp_dsp/sound/AM3E_cpp_matlab.wav',y,Fs);