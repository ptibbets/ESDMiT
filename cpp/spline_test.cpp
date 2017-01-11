#include <iostream>
#include <Spline.h>

int main(void) {
    Eigen::VectorXd x(8);
    Eigen::VectorXd y(8);
    Eigen::VectorXd xx(8);
    x << 0, 1, 2, 3, 4, 5, 6, 7;
    y << 0, 1, 0, 1, 0, 1, 0, 1;
    xx << 0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5;
    helpers::Spline aSpline(x, y);
    for (int i = 0; i < xx.size(); ++i) {
        std::cout << aSpline(xx[i]) << ", ";
    }
    return 0;
}
