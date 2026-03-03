clear all; close all; clc;
%% Чтение файла
fid = fopen('C:\Users\morda\Desktop\Signals\Task\FM3E_fs_24000_float_12_16_56.bin');
y = fread(fid,inf,"single");
fclose(fid);
Fs = 24000;

%% Формирование I Q компонент
I = y(1:2:end);
Q = y(2:2:end);

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
z_norm = audio / abs(max(audio));

%% Запись 
audiowrite('C:\Users\morda\Desktop\Signals\Task\new_FM3E_bin.wav',z_norm,Fs);

%% Сформируем I и Q обратно
%II = real(z_norm(1:1:end));
%QQ = imag(z_norm(1:1:end));

%for i=1:length(II+1)
%    final(2*i-1) = II(i);
%    final(2*i) = QQ(i);
%end


%% Иной способ вычисления фазы 
% Вычисление фазы
%phase1 = angle(comp_signal);

% Вычисление производной
%audio = diff(phase);                            % audio меньше phase на 1 отсчёт
