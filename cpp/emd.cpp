#include "emd.h"
#include "helpers/diff.h"
#include "helpers/Spline.h"

#include <iostream>

void findMinMax(Eigen::VectorXd &vDiff, Eigen::VectorXd &vMins, Eigen::VectorXd &vMaxes)
{
    std::size_t aMinLength = 0, aMaxLength = 0;
    vMaxes[aMaxLength++] = 0;
    vMins[aMinLength++] = 0;
    for(auto aIndex = 1; aIndex < vDiff.rows() - 2; aIndex++)
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

    if(vMaxes[aMaxLength] != vDiff.rows() - 1)
    {
        vMaxes[aMaxLength++] = vDiff.rows();
    }
    if(vMins[aMinLength] != vDiff.rows() - 1)
    {
        vMins[aMinLength++] = vDiff.rows();
    }
    vMaxes = vMaxes.block(0, 0, aMaxLength, 1);
    vMins = vMins.block(0, 0, aMinLength, 1);
}

Eigen::VectorXd getEnv(Eigen::VectorXd &vX, Eigen::VectorXd &vAllVals)
{
    Eigen::VectorXd aYY(vAllVals.rows());
    Eigen::VectorXd aY(vX.rows());
    for(auto aIndex = 0; aIndex < aY.rows(); aIndex++)
    {
        aY[aIndex] = vAllVals[vX[aIndex]];
    }
    helpers::Spline aSpline(vX, aY);
    for(auto aIndex = 0; aIndex < aYY.rows(); aIndex++)
    {
        aYY[aIndex] = aSpline(aIndex);
    }
    return aYY;
}

std::vector<Eigen::VectorXd> emd(Eigen::VectorXd const &vSamples)
{
    std::vector<Eigen::VectorXd> aIMF;
    auto aSamples = vSamples;

    while(true)
    {
        auto aH = aSamples;
        double aSD = 1;

        try
        {
            while(aSD > 0.3)
            {
                auto aDiff = helpers::diff(aH);
                Eigen::VectorXd aMaxes(vSamples.rows());
                Eigen::VectorXd aMins(vSamples.rows());
                findMinMax(aDiff, aMins, aMaxes);
                auto aMaxEnv = getEnv(aMaxes, aH);
                auto aMinEnv = getEnv(aMins, aH);
                auto aMean = (aMaxEnv + aMinEnv) / 2;
                auto aPrevH = aH;
                aH -= aMean;
                aSD = ((aPrevH - aH).cwiseProduct(aPrevH - aH)).cwiseQuotient(aPrevH.cwiseProduct(aPrevH) + Eigen::VectorXd::Ones(aH.rows()) * 0.001).sum();
            }
        }
        catch(std::exception &e)
        {
            break;
        }
        aIMF.push_back(aH);
        aSamples -= aH;
    }

    return aIMF;
}
