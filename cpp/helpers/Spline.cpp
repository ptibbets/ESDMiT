#include "Spline.h"

using namespace helpers;

double Spline::scaledValue(double vX) const
{
    return (vX - mXMin) / (mXMax - mXMin);
}

Eigen::RowVectorXd Spline::scaledValues(Eigen::VectorXd const &vX) const
{
    return vX.unaryExpr([this](double vXval) {return scaledValue(vXval);}).transpose();
}

Spline::Spline(Eigen::VectorXd const &vX, Eigen::VectorXd const &vY) :
        mXMin(vX.minCoeff()),
        mXMax(vX.maxCoeff()),
        mSpline(Eigen::SplineFitting<Eigen::Spline<double, 1>>::Interpolate(
                vY.transpose(),
                std::min<int>(vX.rows() - 1, 4),
                scaledValues(vX))) {}

double Spline::operator()(double vX) const
{
    return mSpline(scaledValue(vX))(0);
}
