#pragma once

#include <Eigen/Eigen>
#include <vector>

Eigen::VectorXd filter(std::vector<Eigen::VectorXd> &vIMFs, std::size_t vStartIMF);
