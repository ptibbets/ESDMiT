#include "diff.h"

Eigen::VectorXd helpers::diff(Eigen::VectorXd const & vVector)
{
    Eigen::VectorXd aVec(vVector.size() - 1);

    for(auto aIndex = 0; aIndex < aVec.size(); aIndex++)
    {
        aVec[aIndex] = vVector[aIndex + 1] - vVector[aIndex];
    }

    return aVec;
}
