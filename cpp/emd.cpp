#include "emd.h"
#include "helpers/diff.h"
#include "helpers/Vector.h"

void findMinMax(Eigen::VectorXd &vDiff, helpers::Vector<Eigen::VectorXi> &vMins, helpers::Vector<Eigen::VectorXi> &vMaxes)
{
    for(auto aIndex = 1; aIndex < vDiff.size() - 3; aIndex++)
    {
        if((vDiff[aIndex] == 0) && (vDiff[aIndex - 1] > 0) && (vDiff[aIndex + 1] < 0))
        {
            vMaxes.pushBack(aIndex);
        }
        else if((vDiff[aIndex] == 0) && (vDiff[aIndex - 1] < 0) && (vDiff[aIndex + 1] > 0))
        {
            vMins.pushBack(aIndex);
        }
        else if((vDiff[aIndex] > 0) && (vDiff[aIndex + 1] < 0))
        {
            vMaxes.pushBack(aIndex + 1);
        }
        else if((vDiff[aIndex] < 0) && (vDiff[aIndex + 1] > 0))
        {
            vMins.pushBack(aIndex + 1);
        }
    }
}

std::vector<Eigen::VectorXd> emd(Eigen::VectorXd const &vSamples)
{
    std::vector<Eigen::VectorXd> aIMF;
    Eigen::VectorXd aMaxes(vSamples.size());
    Eigen::VectorXd aMins(vSamples.size());
    auto aSamples = vSamples;

    while(true)
    {
        auto aH = aSamples;
        double aSD = 1;

        while(aSD > 0.3)
        {
//            auto aDiff = helpers::diff(aH);
        }
    }

    return aIMF;
}
