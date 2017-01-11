#include "filter.h"
#include <exception>

Eigen::VectorXd filter(std::vector<Eigen::VectorXd> &vIMFs, std::size_t vStartIMF)
{
    Eigen::VectorXd aSignal(vIMFs[0].rows());
    if(vStartIMF >= vIMFs.size())
    {
        throw std::invalid_argument("Invalid start IMF number");
    }
    else
    {
        do
        {
            aSignal += vIMFs[vStartIMF++];
        } while(vStartIMF < vIMFs.size());
    }
    return aSignal;
}
