#include <iostream>
#include <Spline.h>

int main(void) {
    Eigen::VectorXd x(8);
    Eigen::VectorXd y(8);
    Eigen::VectorXd xx(18);
    x << 0, 1, 2, 3, 4, 5, 6, 7;
    y << 0, 1, 0, 1, 0, 1, 0, 1;
    xx << 0.25, 0.3, 0.5, 0.66, 0.7, 0.9, 1.25, 1.3, 1.5, 1.66, 1.7, 1.9, 2.25, 2.3, 2.5, 2.66, 2.7, 2.9;
    helpers::Spline aSpline(x, y);
    for (int i = 0; i < xx.size(); ++i) {
        std::cout << aSpline(xx[i]) << " ";
    }
    return 0;
}
