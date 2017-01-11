#include <iostream>
#include <unsupported/Eigen/Splines>

int main(void) {
    Eigen::RowVectorXd knots(8);
    Eigen::RowVectorXd ctrls(8);
    Eigen::RowVectorXd chkpt(18);
    knots << 0, 1, 2, 3, 4, 5, 6, 7;
    ctrls << 0, 1, 0, 1, 0, 1, 0, 1;
    chkpt << 0.25, 0.3, 0.5, 0.66, 0.7, 0.9, 1.25, 1.3, 1.5, 1.66, 1.7, 1.9, 2.25, 2.3, 2.5, 2.66, 2.7, 2.9;
    Eigen::Spline<double, 1, 3> aSpline(knots, ctrls);
    for (int i = 0; i < chkpt.size(); ++i) {
        std::cout << aSpline(chkpt[i]) << std::endl;
    }
    return 0;
}
