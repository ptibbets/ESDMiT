x = [0, 1, 2, 3, 4, 5, 6, 7];
y = [0, 1, 0, 1, 0, 1, 0, 1];
xx = [0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5];
yy = spline(x, y, xx)
yy_cpp = [0, 0.77439, 1, 0.426829, 0, 0.518293, 1, 0.5];
plot(xx, yy, xx, yy_cpp)
