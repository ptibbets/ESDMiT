#pragma once

#include <Eigen/Eigen>
#include <unsupported/Eigen/Splines>

namespace helpers
{
    class Spline
    {
        Eigen::Spline<double, 1> mSpline;
        double mXMin;
        double mXMax;

        double scaledValue(double vX) const;
        Eigen::RowVectorXd scaledValues(Eigen::VectorXd const &vX) const;

    public:
        Spline(Eigen::VectorXd const &vX, Eigen::VectorXd const &vY);
        double operator()(double vX) const;
    };
}
