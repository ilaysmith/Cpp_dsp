close all; clc ; clear all; 
%% Чтение файла
[y,Fs] = audioread('C:\Users\morda\Desktop\Signals\Task\2.149900_26_08_24_12_16_56_F3E.iqw');
% Тип модуляции FM. Fs = 24000

%% Формирование сигнала

I = y(:,1);
Q = y(:,2);

comp_signal = I + 1i*Q;

%% Вычисление фазы
% Частное двух комплексных отсчётов. Фаза между ними

for i = 1:(length(comp_signal) - 1)
    audio(i) = angle((comp_signal(i+1))*conj((comp_signal(i))));
end

audio = audio.';

% Проход по всем значениям
for i = 1:length(audio)
    if audio(i) > pi
        % Положительный скачок
        audio(i) = audio(i) - 2*pi; 
    elseif audio(i) < -pi
        % Отрицательный скачок 
        audio(i) = audio(i) + 2*pi;  
    end
end
%% Фильтрация с помощью обнуления постоянной составляющей

% не требуется, потому что её нет

%% Нормируем 

z = audio / max(abs(audio));

%% Запись файла
audiowrite('C:\Users\morda\Desktop\Signals\Task\new_F3E_IQW.wav',z , Fs);

