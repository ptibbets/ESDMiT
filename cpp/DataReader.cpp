#include "DataReader.h"

Eigen::VectorXd DataReader::getSignal(std::size_t vSignalNumber)
{
    auto aSampleCount = mSignalInfo[vSignalNumber].nsamp;
    Eigen::VectorXd aVector(aSampleCount);
    int aSamples[WFDB_MAXSIG];
    auto aSampleNumber = 0;
    while(getvec(aSamples) >= 0)
    {
        double aSample = static_cast<double>(aSamples[vSignalNumber]);
        aSample -= mSignalInfo[vSignalNumber].adczero;
        aSample /= mSignalInfo[vSignalNumber].gain;
        aVector[aSampleNumber++] = aSample;
    }

    return aVector;
}

DataReader::DataReader(std::string vPath, std::string vRecordName) throw(std::runtime_error)
{
    mDataVectors.clear();
    setwfdb(const_cast<char*>(vPath.c_str()));
    if(isigopen(const_cast<char*>(vRecordName.c_str()), mSignalInfo, sizeof(mSignalInfo)) < 1)
    {
        throw std::runtime_error("Cannot open record");
    }
    for(auto aIndex = 0; aIndex < sizeof(mSignalInfo) / sizeof(WFDB_Siginfo); aIndex++)
    {
        mDataVectors.push_back(getSignal(aIndex));
    }
}

Eigen::VectorXd & DataReader::getData(std::size_t vSignalNumber)
{
    return mDataVectors[vSignalNumber];
}
