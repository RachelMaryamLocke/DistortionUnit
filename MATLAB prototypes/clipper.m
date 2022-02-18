function [y] = clipper(x, type, upperClipLevel, lowerClipLevel, alpha)
%perform hard or arctan soft clipping based on the users choice for 'type'

if type == "hard"
    for n = 1:length(x)
        if x(n,1) > upperClipLevel
            y(n,1) = upperClipLevel;
        elseif x(n,1) <= -lowerClipLevel
            y(n,1) = -lowerClipLevel;
        else 
            y(n,1) = x(n,1);
        end
    end
elseif type == "soft"
    for n = 1:length(x)
        y(n,1) = (2/pi) * atan(alpha * x(n,1));
    end
end
end