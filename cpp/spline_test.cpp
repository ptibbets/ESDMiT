#include <iostream>
#include <Spline.h>
#include "DataWriter.h"

int main(void) {
    Eigen::VectorXd x(8);
    Eigen::VectorXd y(8);
    Eigen::VectorXd xx(1000);
    Eigen::VectorXd yy(xx.size());
    x << 0, 1, 2, 3, 4, 5, 6, 7;
    y << 0, 1, 0, 1, 0, 1, 0, 1;
    helpers::Spline aSpline(x, y);
    double v = 0.0;
    for (int i = 0; i < xx.size(); ++i) {
        v += 0.003;
        xx[i] = v;
        yy[i] = aSpline(xx[i]);
    }
    std::vector<Eigen::VectorXd> vec = {x, y, xx, yy };
    writeData("../out.mat", vec);
    return 0;
}
