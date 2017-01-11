#include "emd.h"
#include "helpers/diff.h"
#include "helpers/Spline.h"

void findMinMax(Eigen::VectorXd &vDiff, Eigen::VectorXd &vMins, Eigen::VectorXd &vMaxes,
        std::size_t &vMinLength, std::size_t &vMaxLength)
{
    vMinLength = vMaxLength = 0;
    vMaxes[vMaxLength++] = 0;
    vMins[vMinLength++] = 0;
    for(auto aIndex = 1; aIndex < vDiff.rows() - 2; aIndex++)
    {
        if((vDiff[aIndex] == 0) && (vDiff[aIndex - 1] > 0) && (vDiff[aIndex + 1] < 0))
        {
            vMaxes[vMaxLength++] = aIndex;
        }
        else if((vDiff[aIndex] == 0) && (vDiff[aIndex - 1] < 0) && (vDiff[aIndex + 1] > 0))
        {
            vMins[vMinLength++] = aIndex;
        }
        else if((vDiff[aIndex] > 0) && (vDiff[aIndex + 1] < 0))
        {
            vMaxes[vMaxLength++] = aIndex + 1;
        }
        else if((vDiff[aIndex] < 0) && (vDiff[aIndex + 1] > 0))
        {
            vMins[vMinLength++] = aIndex + 1;
        }
    }

    if(vMaxLength + vMinLength < 4)
    {
        throw std::exception();
    }

    if(vMaxes[vMaxLength] != vDiff.rows())
    {
        vMaxes[vMaxLength++] = vDiff.rows();
    }
    if(vMins[vMinLength] != vDiff.rows())
    {
        vMins[vMinLength++] = vDiff.rows();
    }
}

Eigen::VectorXd getEnv(Eigen::VectorXd &vX, std::size_t &vXLength, Eigen::VectorXd &vAllVals)
{
    Eigen::VectorXd aYY(vAllVals.rows());
    Eigen::VectorXd aX(vXLength);
    Eigen::VectorXd aY(vXLength);
    for(auto aIndex = 0; aIndex < aY.rows(); aIndex++)
    {
        aX[aIndex] = vX[aIndex];
        aY[aIndex] = vAllVals[aX[aIndex]];
    }
    helpers::Spline aSpline(aX, aY);
    for(auto aIndex = 0; aIndex < aYY.rows(); aIndex++)
    {
        aYY[aIndex] = aSpline(aIndex);
    }
    return aYY;
}

double getNewSD(Eigen::VectorXd &vNewH, Eigen::VectorXd &vOldH)
{
    auto aNom = (vOldH - vNewH).cwiseProduct(vOldH - vNewH);
    auto aDen = vOldH.cwiseProduct(vOldH) + Eigen::VectorXd::Ones(vOldH.rows()) * 0.001;
    auto aSD = aNom.cwiseQuotient(aDen).sum();
    return aSD;
}

std::vector<Eigen::VectorXd> emd(Eigen::VectorXd const &vSamples)
{
    std::vector<Eigen::VectorXd> aIMF;
    auto aSamples = vSamples;
    Eigen::VectorXd aMaxes(vSamples.rows());
    Eigen::VectorXd aMins(vSamples.rows());
    std::size_t aMaxLength;
    std::size_t aMinLength;

    while(true)
    {
        auto aH = aSamples;
        double aSD = 1;

        try
        {
            while(aSD > 0.3)
            {
                auto aDiff = helpers::diff(aH);
                findMinMax(aDiff, aMins, aMaxes, aMinLength, aMaxLength);
                auto aMaxEnv = getEnv(aMaxes, aMaxLength, aH);
                auto aMinEnv = getEnv(aMins, aMinLength, aH);
                auto aMean = (aMaxEnv + aMinEnv) / 2;
                auto aPrevH = aH;
                aH -= aMean;
                aSD = getNewSD(aH, aPrevH);
            }
        }
        catch(std::exception &e)
        {
            aIMF.push_back(aH);
            break;
        }
        aIMF.push_back(aH);
        aSamples -= aH;
    }

    return aIMF;
}
