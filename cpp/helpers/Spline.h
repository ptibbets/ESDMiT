#pragma once
#include <Eigen/Eigen>
#include "alglib/interpolation.h"

namespace helpers {

    class Spline {
        alglib::spline1dinterpolant mSpline;

    public:
        Spline(Eigen::VectorXd const &vX, Eigen::VectorXd const &vY);
        double operator()(double vX) const;
    };

}
