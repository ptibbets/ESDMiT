#include <iostream>
#include <eigen3/Eigen/Dense>

#include "helpers/diff.h"

using Eigen::VectorXd;

int main()
{
    VectorXd v;
    v.resize(2);
    v[0] = 2;
    v[1] = 5;

    std::cout << v << std::endl;

    auto a = diff(v);

    std::cout << a << std::endl;

//  MatrixXd m(2,2);
//  m(0,0) = 3;
//  m(1,0) = 2.5;
//  m(0,1) = -1;
//  m(1,1) = m(1,0) + m(0,1);
//  std::cout << m << std::endl;
}
