#include "emd.h"
#include "helpers/diff.h"

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
            auto aDiff = diff(aH);
        }
    }

    return aIMF;
}
