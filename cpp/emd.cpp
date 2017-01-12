#include <numeric>
#include "emd.h"
#include "helpers/FindExtremum.h"
#include "helpers/Spline.h"

double compute_SD(Eigen::VectorXd &h, Eigen::VectorXd &prevh, double eps)
{
    auto aNom = (prevh - h).cwiseProduct(prevh - h);
    auto aDen = prevh.cwiseProduct(prevh) + Eigen::VectorXd::Ones(prevh.rows()) * eps;
    auto aSD = aNom.cwiseQuotient(aDen).sum();
    return aSD;
}

Eigen::VectorXd at(Eigen::VectorXd vIdxs, Eigen::VectorXd vData) {
    Eigen::VectorXd aData(vIdxs.size());
    for (int i = 0; i < (int)vIdxs.size(); ++i)
        aData[i] = vData[(std::size_t)vIdxs[i]];
    return aData;
}

std::vector<Eigen::VectorXd> emd(Eigen::VectorXd const &vData, double vThreshold, double vEps)
{
    std::vector<Eigen::VectorXd> imfs;
    Eigen::VectorXd c = vData;
    std::size_t n = vData.size();
    std::size_t ext_count;
    while (true) {
        Eigen::VectorXd prevh;
        Eigen::VectorXd h = c;
        double SD = std::numeric_limits<double>::max();
        while (SD > vThreshold) {
            Eigen::VectorXd maxs;
            Eigen::VectorXd mins;
            ext_count = helpers::findminmax(h, mins, maxs);
            if (ext_count < 2)
                break;
            helpers::Spline maxspl(maxs, at(maxs, h));
            helpers::Spline minspl(mins, at(mins, h));
            Eigen::VectorXd maxenv(vData.size());
            Eigen::VectorXd minenv(vData.size());
            for (int i = 0; i < (int)vData.size(); ++i) {
                maxenv[i] = maxspl((double)i);
                minenv[i] = minspl((double)i);
            }
            Eigen::VectorXd m = (maxenv + minenv) / 2;
            prevh = h;
            h = h - m;
            SD = compute_SD(h, prevh, vEps);
        }
        imfs.push_back(h);
        if (ext_count < 2)
            break;
    }
    return imfs;
}
