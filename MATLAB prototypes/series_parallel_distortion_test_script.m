close all; clear; clc;

%test sine 
Fs = 48000;
T = 1/Fs;
f = 200;
t = (0:T:1).';
x = sin(2 * pi * f * t);

level = 0.5;
hard_gain = 1;

%% full-wave rectification

rect_out = level * fullWaveRectification(x);

[fullWaveRender, Fs] = audioread('rectRender.wav');

plot(rect_out)
hold on
plot(fullWaveRender(:,1))
grid on
hold off
title("Full Wave Rectification (MATLAB Render vs C++ Render)", "FontSize",14)
legend("MATLAB Render", "C++ Render")
xlabel("sample(n)")
ylabel("amplitude")
xlim([0 2400])

figure(2)
plot(linspace(0,Fs,length(rect_out)), 20*log10(abs(fft(rect_out))))
hold on
plot(linspace(0,Fs,length(fullWaveRender(:,1))), 20*log10(abs(fft(fullWaveRender(:,1)))))
grid on
title("C++ Render Vs MATLAB Render Full Wave Rectification", "FontSize",14)
legend("MATLAB Render", "C++ Render")
xlabel("frequency(Hz)")
ylabel("magnitude")
xlim([0 8000])
ylim([0 100])

%% arctangent soft clipping

clip_out = level * clipper(x, "soft", 1, 1, 8);

[arcClipRender, Fs] = audioread('arcClipRender.wav');

plot(clip_out)
hold on
plot(arcClipRender(:,1))
grid on
hold off
title("Arctangent Soft Clipping \alpha = 8 (MATLAB Render vs C++ Render)", "FontSize",14)
legend("MATLAB Render", "C++ Render")
xlabel("sample(n)")
ylabel("amplitude")
xlim([0 2400])

figure(2)
plot(linspace(0,Fs,length(arcClipRender(:,1))), 20*log10(abs(fft(arcClipRender(:,1)))))
hold on
plot(linspace(0,Fs,length(clip_out)), 20*log10(abs(fft(clip_out))))
grid on
title("C++ Render Vs MATLAB Render Arctangent Soft Clipping \alpha = 8", "FontSize",14)
legend("C++ Render", "MATLAB Render")
xlabel("frequency(Hz)")
ylabel("magnitude")
xlim([0 8000])
ylim([0 100])

%% Bit Reduction

bit_out = level * bitCrusher(x,4);

[bitCrushRender, Fs] = audioread('bitCrushRender.wav');

plot(bit_out)
hold on
plot(bitCrushRender(:,1))
grid on
hold off
title("Bit Reduction (MATLAB Render vs C++ Render)", "FontSize",14)
legend("MATLAB Render", "C++ Render (4bit)")
xlabel("sample(n)")
ylabel("amplitude")
xlim([0 1200])
 
figure(2)
plot(linspace(0,Fs,length(bit_out)), 20*log10(abs(fft(bit_out))))
hold on
plot(linspace(0,Fs,length(bitCrushRender(:,1))), 20*log10(abs(fft(bitCrushRender(:,1)))))
grid on
title("MATLAB vs C++ Render Bit Reduction Bit Depth = 4", "FontSize",14)
legend("MATLAB Render", "C++ Render")
xlabel("frequency(Hz)")
ylabel("magnitude")
xlim([0 1800])
ylim([0 100])

%% hard clipping

clip_out = level * clipper(hard_gain * x, "hard", 0.7, 0.7, 1);

[hardClipRender, Fs] = audioread('hardClipRender.wav');

plot(clip_out)
hold on 
plot(hardClipRender(:,1))
hold off
grid on
title("MATLAB vs C++ Render Hard Clipping Clip Level 0.7", "FontSize",14)
legend("MATLAB Render", "C++ Render")
xlabel("sample(n)")
ylabel("amplitude")
xlim([0 2400])

figure(2)
plot(linspace(0,Fs,length(hardClipRender(:,1))), 20*log10(abs(fft(hardClipRender(:,1)))))
hold on
plot(linspace(0,Fs,length(clip_out)), 20*log10(abs(fft(clip_out))))
grid on
title("MATLAB vs C++ Render Hard Clipping Clip Level 0.7", "FontSize",14)
legend("C++ Render", "MATLAB Render")
xlabel("frequency(Hz)")
ylabel("magnitude")
xlim([0 2400])
ylim([0 100])
