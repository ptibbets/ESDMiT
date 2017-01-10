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

    Eigen::VectorXd getSignal(std::size_t vSignalNumber);

public:
    DataReader(std::string vPath, std::string vRecordName) throw(std::runtime_error);
    Eigen::VectorXd & getData(std::size_t vSignalNumber);
};
