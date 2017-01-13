function [ sf ] = emd_filter( imfs, d )

sf = zeros(1,size(imfs, 2));
it = d;
while(it < size(imfs, 1))
    it = it + 1;
    sf = sf + imfs(it,:);
end

end

