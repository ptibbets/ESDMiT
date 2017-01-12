#include <iostream>
#include "DataWriter.h"
#include "emd.h"
#include "helpers/FindExtremum.h"
#include "helpers/Spline.h"

void fe() {
    Eigen::VectorXd x(20);
    x << 0, 1, 0, 2, 3, 3, 3, 4, 5, 4, 3, 2, 3, 2, 3, 2, 4, 4, 4, 3;
    Eigen::VectorXd min;
    Eigen::VectorXd max;
    helpers::findminmax(x, min, max);
}

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
    writeVectors("../out.mat", vec);
    return 0;
}
