clear all; close all; clc;
% fopen - открывает файл и возвращает идентификатор файла для чтений
% fread - читает файл по идентификатору
% audioread - читает аудифайлы. На выходе отчёты y и Fs. Из себя y
% представляет массив левого и правого канала. Если обнулить второй массив, то пропадёт звук из правого наушника -> каналы независимы 
% audiowrite - записывает аудиоданные в файл
% wavread отсутствует в новых версиях матлаб

%% Чтение данных
%samples = [1,2*Fs]; % вот так можно записать конкретные секунды
[y,Fs] = audioread('C:\Users\morda\Desktop\Signals\Task\1.053000_11.01.2022 10_43_02  A3E.iqw');
%% Формирование огибающей
% Воспользуемся auidoread, так как он даёт Fs и, в теории, нужный тип дан-х
signal = sqrt(y(:,1).^2 + y(:,2).^2); % огибающая 

%% Фильтрация с помощью обнуления постоянной составляющей

z = signal - mean(signal);

%% Запись файла
audiowrite('C:\Users\morda\Desktop\Signals\Task\new_A3E_IQW.wav',z,Fs); % звук стал менее звенящим

%% Доп

%{
%% Спектр сигнала
Y = fft(y);
T = 1/Fs;
L = length(y); % длина сигнала

k = (0:L-1)*T; 

figure;
plot(k,y)
hold on
grid on
title("Дискретный сигнал")
xlabel("k")
ylabel("X(k)")

figure;
plot(Fs/L*(0:L-1),abs(Y),"LineWidth",3)
hold on
grid on
title("БПФ")
xlabel("f (Гц)")
ylabel("|fft(X)|")

figure
plot(Fs/L*(-L/2:L/2-1),abs(fftshift(Y)),"LineWidth",3)
title("Спектр БПФ на положительных и отрицательных частотах")
xlabel("f (Гц)")
ylabel("|fft(X)|")



%% Сигнал в спектральной области и во временной после фильтрации

figure;
plot(Fs/L*(0:L-1),abs(z),"LineWidth",3)
hold on
grid on
title("Комплексная величина спектра БПФ")
xlabel("f (Гц)")
ylabel("|fft(X)|")

figure;
plot(k,z,"LineWidth",3)
hold on
grid on
title("Сигнал после фильтра")
xlabel("k")
ylabel("X(k)")

figure
plot(Fs/L*(-L/2:L/2-1),abs(fftshift(z)),"LineWidth",3)
title("Спектр БПФ на положительных и отрицательных частотах")
xlabel("f (Гц)")
ylabel("|fft(X)|")
%}