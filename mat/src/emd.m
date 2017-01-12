function imf = emd(x)

    c = x(:)';
    N = length(x);

    imf = [];

    while (1)
       h = c;
       SD = 1;

       while SD > 0.3
          d = diff(h);
          maxmin = [];
          maxes = [];
          mins = [];
          for i = 2:N - 2
             if d(i) == 0 && d(i - 1) > 0 && d(i + 1) < 0
                maxes = [maxes, i];
             elseif d(i) == 0 && d(i - 1) < 0 && d(i + 1) > 0
                 mins = [mins, i];
             elseif d(i) > 0 && d(i + 1) < 0
                 maxes = [maxes, i + 1];
             elseif d(i) < 0 && d(i + 1) > 0
                 mins = [mins, i + 1];
             end
%              if d(i) == 0 && ((d(i - 1) > 0 && d(i + 1) < 0) || ...
%                      (d(i - 1) < 0 && d(i + 1) > 0))
%                 maxmin = [maxmin, i];
%              elseif sign(d(i)) ~= sign(d(i + 1))
%                 maxmin = [maxmin, i + 1];
%              end
          end

          if size(maxes, 2) + size(mins, 2) < 2
             break
          end

%           if maxmin(1) > maxmin(2)
%              maxes = maxmin(1:2:length(maxmin));
%              mins  = maxmin(2:2:length(maxmin));
%           else
%              maxes = maxmin(2:2:length(maxmin));
%              mins  = maxmin(1:2:length(maxmin));
%           end
          
          if(maxes(1) ~= 1)
              maxes = [1 maxes];
          end
          if(maxes(length(maxes)) ~= N)
              maxes = [maxes N];
          end
          if(mins(1) ~= 1)
              mins = [1 mins];
          end
          if(mins(length(mins)) ~= N)
              mins = [mins N];
          end

          maxenv = spline(maxes, h(maxes), 1:N);
          minenv = spline(mins, h(mins), 1:N);

          m = (maxenv + minenv) / 2;
          prevh = h;
          h = h - m;

          eps = 0.001;
          SD = sum (((prevh - h) .^ 2) ./ (prevh .^ 2 + eps));

       end

       imf = [imf; h];

       if size(maxes, 2) + size(mins, 2) < 2
          break
       end

       c = c - h;

    end
end
