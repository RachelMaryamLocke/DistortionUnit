function [y] = fullWaveRectification(x)
%perform full-wave rectification
for n = 1:length(x)
    if x(n,1) >= 0
        y(n,1) = x(n,1);
    elseif x(n,1) < 0 
        y(n,1) = -1 * x(n,1);
    end
end
end
