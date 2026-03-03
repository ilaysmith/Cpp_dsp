clear all; close all; clc;

%% Чтение файла 
% Содержит просто данные: читаем через fread 
fid = fopen('C:\Users\morda\Desktop\Signals\Task\AM3E_fs_24000_float_10_43_02.bin');
y = fread(fid, inf, 'single'); % в матлаб аналог float это single 
Fs = 24000; % задана в названии
% получили отсчёты комплексного сигнала

%% Формирование I/Q компонент

I = y(1:2:end);
Q = y(2:2:end);
audio = sqrt(I.^2 + Q.^2); % огибающая

%% Фильтрация с помощью обнуления постоянной составляющей

z = audio - mean(audio);

%% Нормируем
final = z / max(abs(z)); % чтобы при записи данные не были обрезаны
% тк, если число выходит за [-1;1], то audiowrite даёт ошибку, что файлы
% обрезаны.

%% Запись сигнала
audiowrite('C:\Users\morda\Desktop\Signals\Task\new_AM3E_bin.wav',final,Fs);

%% Доп

%{
%% Спектр сигнала
Y = fft(y);
T = 1/Fs;
L = length(y); % длина сигнала

t = (0:L-1)*T; % вектор времени

figure;
plot(t,y)
hold on
grid on
title("Сигнал во временной области")
xlabel("t")
ylabel("X(t)")

figure;
plot(Fs/L*(0:L-1),abs(Y),"LineWidth",3)
hold on
grid on
title("Комплексная величина спектра БПФ")
xlabel("f (Гц)")
ylabel("|fft(X)|")

figure
plot(Fs/L*(-L/2:L/2-1),abs(fftshift(Y)),"LineWidth",3)
title("Спектр БПФ на положительных и отрицательных частотах")
xlabel("f (Гц)")
ylabel("|fft(X)|")

% В данном случае запись сигнала не разборчива


%% Сигнал в спектральной области и во временной после фильтрации

figure;
plot(Fs/L*(0:L-1),abs(z),"LineWidth",3)
hold on
grid on
title("Комплексная величина спектра БПФ")
xlabel("f (Гц)")
ylabel("|fft(X)|")

figure;
plot(t,z,"LineWidth",3)
hold on
grid on
title("Сигнал после фильтра")
xlabel("t")
ylabel("X(t)")

figure
plot(Fs/L*(-L/2:L/2-1),abs(fftshift(z)),"LineWidth",3)
title("Спектр БПФ на положительных и отрицательных частотах")
xlabel("f (Гц)")
ylabel("|fft(X)|")
%}