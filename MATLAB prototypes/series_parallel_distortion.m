close all; clear; clc;

%test sine 
Fs = 48000;
T = 1/Fs;
f = 200;
t = (0:T:1).';
x = sin(2 * pi * f * t);
level = 0.5; %output gain
series_wet = 0.5; 
parallel_wet = 1 - series_wet;
hard_gain = 10;

%SERIES DISTORTIONS

%bit reduction 
bit_depth = 2;
bit_out = bitCrusher(x, bit_depth);

%full-wave rectification
series_out = fullWaveRectification(bit_out);

%PARALLEL DISTORTIONS
parallel_out = clipper(hard_gain * x, "hard", 0.2, 0.2, 1);

%OUTPUT 
y = level * (series_wet * series_out + parallel_wet * parallel_out);