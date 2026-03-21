clear all; close all; clc;

%% Чтение файла 
% Содержит просто данные: читаем через fread

fid = fopen('/home/morda/task_for_stc_1/dsp_my/dsp_my/AM3E_cpp.bin');
% '/home/morda/task_for_stc_1/dsp_my/dsp_my/AM3E_cpp.bin
% 
y = fread(fid, inf, 'single'); % в матлаб аналог float это single 
Fs = 24000; % задана в названии
% получили отсчёты комплексного сигнала

%% Запись сигнала
audiowrite('/home/morda/task_for_stc_1/Cpp_dsp/sound/CPP_AM_BIN_TEST.wav',y,Fs);
% /home/morda/task_for_stc_1/Cpp_dsp/sound/CPP_AM_BIN_TEST.wav'