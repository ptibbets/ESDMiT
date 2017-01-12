function imf = emd(x)
    c = x';
    imf = [];
    idx = 1:length(x);
    while (1)
        h = c;
        SD = inf;
        while SD > 0.3
            [maxes, mins, stop] = findmaxmin(h);
            
            if stop == 1
                break
            end
            
            maxenv = spline(maxes, h(maxes), idx);
            minenv = spline(mins, h(mins), idx);

            m = (maxenv + minenv) / 2;
            prevh = h;
            h = h - m;

            eps = 0.0000001;
            SD = sum (((prevh - h) .^ 2) ./ (prevh .^ 2 + eps));
        end

        imf = [imf; h];

        if size(maxes, 2) + size(mins, 2) < 2
            break
        end

        c = c - h;
    end
end

function [maxes, mins, stop] = findmaxmin(h)
    stop = 0;
    d = diff(h);
    maxes = [];
    mins = [];
    for i = 2:length(h) - 2
        if d(i) == 0 && d(i - 1) > 0 && d(i + 1) < 0
            maxes = [maxes, i];
        elseif d(i) == 0 && d(i - 1) < 0 && d(i + 1) > 0
            mins = [mins, i];
        elseif d(i) > 0 && d(i + 1) < 0
            maxes = [maxes, i + 1];
        elseif d(i) < 0 && d(i + 1) > 0
            mins = [mins, i + 1];
        end
    end
    
    if length(maxes) + length(mins) < 2
      	stop = 1;
    end

    if(isempty(maxes) || maxes(1) ~= 1)
    	maxes = [1 maxes];
    end
    if(maxes(end) ~= length(h))
     	maxes = [maxes length(h)];
    end
    if(isempty(mins) || mins(1) ~= 1)
     	mins = [1 mins];
    end
    if(mins(end) ~= length(h))
        mins = [mins length(h)];
    end
end
