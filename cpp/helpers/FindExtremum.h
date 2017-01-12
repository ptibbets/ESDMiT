#pragma once
#include <Eigen/Eigen>

namespace helpers {

    std::size_t findminmax(const Eigen::VectorXd& vData, Eigen::VectorXd& vMin, Eigen::VectorXd& vMax);

}
