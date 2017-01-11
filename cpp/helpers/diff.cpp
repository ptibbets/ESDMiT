#include "diff.h"
#include <cmath>

Eigen::VectorXd helpers::diff(Eigen::VectorXd const & vVector)
{
    Eigen::VectorXd aVec(vVector.rows() - 1);

    for(auto aIndex = 0; aIndex < aVec.rows(); aIndex++)
    {
        auto aDiff = vVector[aIndex + 1] - vVector[aIndex];
        if(std::isnan(aDiff))
        {
            throw std::exception();
        }
        aVec[aIndex] = aDiff;
    }

    return aVec;
}
