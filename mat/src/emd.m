function imf = emd(x)
    c = x';
    N = length(x);
    imf = [];
    while (1)
        h = c;
        SD = inf;
        while SD > 0.3
            [~, maxs] = findpeaks(h);
            [~, mins] = findpeaks(-h);

            if(isempty(maxs) || maxs(1) ~= 1)
                maxs = [1 maxs];
            end
            if(maxs(end) ~= N)
                maxs = [maxs N];
            end
            if(isempty(mins) || mins(1) ~= 1)
                mins = [1 mins];
            end
            if(mins(end) ~= N)
                mins = [mins N];
            end

          	if size(maxs, 2) + size(mins, 2) < 6
                break
           	end

            maxenv = spline(maxs, h(maxs), 1:N);
            minenv = spline(mins, h(mins), 1:N);

            m = (maxenv + minenv) / 2;
            prevh = h;
            h = h - m;

            eps = 0.0000001;
            SD = sum (((prevh - h) .^ 2) ./ (prevh .^ 2 + eps));
        end

        imf = [imf; h];

        if size(maxs, 2) + size(mins, 2) < 6
            break
        end

        c = c - h;
    end
end
