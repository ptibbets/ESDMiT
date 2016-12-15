function [ sf ] = emd_filter( s, d )

imfs = emd(s)';
imfss = size(imfs);

sf = zeros(size(s));
it = d;
while(it < imfss(2))
    it = it + 1;
    sf = sf + imfs(:,it);
end

end

