#include <iostream>
#include <unsupported/Eigen/Splines>
//#include <Spline.h>

using namespace Eigen;

Spline<double, 1, 3> closed_spline2d() {
    VectorXd knots(12);
    knots <<
        0,
        0,
        0,
        0,
        0.867193179093898,
        1.660330955342408,
        2.605084834823134,
        3.484154586374428,
        4.252699478956276,
        4.252699478956276,
        4.252699478956276,
        4.252699478956276;

    VectorXd ctrls(8);
    ctrls <<
        -0.370967741935484,
        -0.231401860693277,
        0.344361228532831,
        0.828990216203802,
        0.407270163678382,
        -0.488467813584053,
        -0.494657189446427,
        -0.370967741935484;
    //ctrls.transposeInPlace();

    return Spline<double, 1, 3>(knots, ctrls);
}
void eval_closed_spline2d() {
    auto spline = closed_spline2d();

    VectorXd u(12);
    u <<
        0,
        0.332457030395796,
        0.356467130532952,
        0.453562180176215,
        0.648017921874804,
        0.973770235555003,
        1.882577647219307,
        2.289408593930498,
        3.511951429883045,
        3.884149321369450,
        4.236261590369414,
        4.252699478956276;

    for (int i = 0; i<u.size(); ++i) {
        Vector2d pt = spline(u(i));
    }
}

int main(void) {
    //Eigen::VectorXd x(8);
    //Eigen::VectorXd y(8);
    //Eigen::VectorXd xx(18);
    //x << 0, 1, 2, 3, 4, 5, 6, 7;
    //y << 0, 1, 0, 1, 0, 1, 0, 1;
    //xx << 0.25, 0.3, 0.5, 0.66, 0.7, 0.9, 1.25, 1.3, 1.5, 1.66, 1.7, 1.9, 2.25, 2.3, 2.5, 2.66, 2.7, 2.9;
    //helpers::Spline aSpline(x, y);
    //for (int i = 0; i < xx.size(); ++i) {
    //    std::cout << aSpline(xx[i]) << " ";
    //}

    eval_closed_spline2d();

    return 0;
}
