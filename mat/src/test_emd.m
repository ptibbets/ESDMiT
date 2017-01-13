load('../dat/100.mat')
load('imfs.mat')

imfs_test = emd(signal(1:250,1))';
% sum(sum(imfs-imfs_test))
