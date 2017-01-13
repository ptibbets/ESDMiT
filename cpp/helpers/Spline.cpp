#include "Spline.h"

namespace helpers {

    Spline::Spline(Eigen::VectorXd const &vX, Eigen::VectorXd const &vY) {
        alglib::real_1d_array ax;
        ax.setcontent(vX.size(), vX.data());
        alglib::real_1d_array ay;
        ay.setcontent(vY.size(), vY.data());
        alglib::spline1dbuildcubic(ax, ay, vX.size(), 1, 0, 1, 0, mSpline);
    }

    double Spline::operator()(double vX) const {
        return alglib::spline1dcalc(mSpline, vX);
    }

}
