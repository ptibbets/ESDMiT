#pragma once

#include <string>
#include <vector>
#include <exception>
#include <Eigen/Eigen>
#include <wfdb/wfdb.h>

class DataReader
{
    WFDB_Siginfo mSignalInfo[2];
    std::vector<Eigen::VectorXd> mDataVectors;

    std::size_t mSignalCount = sizeof(mSignalInfo) / sizeof(WFDB_Siginfo);

    Eigen::VectorXd getSignal(std::size_t vSignalNumber, int vDataLength);

public:
    DataReader(std::string vPath, std::string vRecordName, int vDataLength = -1);
    Eigen::VectorXd & getData(std::size_t vSignalNumber);
};
