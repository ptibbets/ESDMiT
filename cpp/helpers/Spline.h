#pragma once

#include <Eigen/Eigen>
#include <unsupported/Eigen/Splines>

namespace helpers
{
    class Spline
    {
        double mXMin;
        double mXMax;
        Eigen::Spline<double, 1> mSpline;

        double scaledValue(double vX) const;
        Eigen::RowVectorXd scaledValues(Eigen::VectorXd const &vX) const;

    public:
        Spline(Eigen::VectorXd const &vX, Eigen::VectorXd const &vY);
        double operator()(double vX) const;
    };
}
