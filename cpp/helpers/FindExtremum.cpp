#include "diff.h"
#include <cmath>

namespace helpers {

    double diff(const Eigen::VectorXd& vData, std::size_t i) {
        return vData[i] - vData[i - 1];
    }

    std::size_t findminmax(const Eigen::VectorXd& vData, Eigen::VectorXd& vMin, Eigen::VectorXd& vMax) {
        std::vector<std::size_t> min(vData.size());
        std::vector<std::size_t> max(vData.size());
        min.push_back(0);
        max.push_back(0);
        std::size_t minc = 1;
        std::size_t maxc = 1;
        double ld = diff(vData, 1);
        for (int i = 1; i < vData.size(); ++i) {
            double d = diff(vData, i);
            if (d > 0 && ld < 0)
                min.push_back(minc);
            if (d < 0 && ld > 0)
                max.push_back(maxc);
            if (d != 0)
                ld = d;
            if (d > 0)
                maxc = i;
            if (d < 0)
                minc = i;
        }
        min.push_back(vData.size() - 1);
        max.push_back(vData.size() - 1);
        vMin.resize(min.size());
        vMax.resize(max.size());
        for (std::size_t i = 0; i < min.size(); ++i) {
            vMin[i] = min[i];
        }
        for (std::size_t i = 0; i < max.size(); ++i) {
            vMax[i] = max[i];
        }
        return min.size() + max.size();
    }

}
