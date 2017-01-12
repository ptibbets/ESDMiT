#include "diff.h"
#include <cmath>

Eigen::VectorXd helpers::diff(Eigen::VectorXd const & vVector)
{
    Eigen::VectorXd aVec(vVector.rows() - 1);
    double aDiff;

    for(auto aIndex = 0; aIndex < aVec.rows(); aIndex++)
    {
        aDiff = vVector[aIndex + 1] - vVector[aIndex];
        aVec[aIndex] = aDiff;
    }

    return aVec;
}
