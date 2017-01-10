#include "emd.h"
#include "helpers/diff.h"
#include "helpers/Vector.h"

void findMinMax(Eigen::VectorXd &vDiff, Eigen::VectorXi &vMins, Eigen::VectorXi &vMaxes)
{
    std::size_t aMinLength = 0, aMaxLength = 0;
    vMaxes[aMaxLength++] = 0;
    vMins[aMinLength++] = 0;
    for(auto aIndex = 1; aIndex < vDiff.size() - 2; aIndex++)
    {
        if((vDiff[aIndex] == 0) && (vDiff[aIndex - 1] > 0) && (vDiff[aIndex + 1] < 0))
        {
            vMaxes[aMaxLength++] = aIndex;
        }
        else if((vDiff[aIndex] == 0) && (vDiff[aIndex - 1] < 0) && (vDiff[aIndex + 1] > 0))
        {
            vMins[aMinLength++] = aIndex;
        }
        else if((vDiff[aIndex] > 0) && (vDiff[aIndex + 1] < 0))
        {
            vMaxes[aMaxLength++] = aIndex + 1;
        }
        else if((vDiff[aIndex] < 0) && (vDiff[aIndex + 1] > 0))
        {
            vMins[aMinLength++] = aIndex + 1;
        }
    }

    if(aMaxLength + aMinLength < 2)
    {
        throw std::exception();
    }

    if(vMaxes[aMaxLength] != vDiff.size() - 1)
    {
        vMaxes[aMaxLength++] = vDiff.size();
    }
    if(vMins[aMinLength] != vDiff.size() - 1)
    {
        vMins[aMinLength++] = vDiff.size();
    }
    vMaxes = vMaxes.block(0, 0, aMaxLength, 1);
    vMins = vMins.block(0, 0, aMinLength, 1);
}

std::vector<Eigen::VectorXd> emd(Eigen::VectorXd const &vSamples)
{
    std::vector<Eigen::VectorXd> aIMF;
    auto aSamples = vSamples;

    while(true)
    {
        auto aH = aSamples;
        double aSD = 1;

        while(aSD > 0.3)
        {
            auto aDiff = helpers::diff(aH);
            Eigen::VectorXi aMaxes(vSamples.size());
            Eigen::VectorXi aMins(vSamples.size());
            try
            {
                findMinMax(aDiff, aMins, aMaxes);
            }
            catch (std::exception &e)
            {
                break;
            }
        }
    }

    return aIMF;
}
