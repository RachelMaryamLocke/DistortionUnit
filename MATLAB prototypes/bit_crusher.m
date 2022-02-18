function [y] = bitCrusher(x, bit_depth)
%perform bit reduction
ampValues = 2^(bit_depth - 1);
for n = 1:length(x)
    y(n,1) = ceil(ampValues * x(n,1)) * (1/ampValues);
end
end
