#pragma once

#include <Eigen/Eigen>
#include <vector>

std::vector<Eigen::VectorXd> emd(Eigen::VectorXd const &vSamples, double vThreshold = 0.3, double vEps = 0.0000001);
