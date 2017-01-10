#include "DataReader.h"

Eigen::VectorXd DataReader::getSignal(std::size_t vSignalNumber, int vDataLength)
{
    auto aSampleCount = mSignalInfo[vSignalNumber].nsamp;
    Eigen::VectorXd aVector(aSampleCount);
    int aSamples[WFDB_MAXSIG];
    auto aSampleNumber = 0;
    while((getvec(aSamples) >= 0) && (vDataLength >= 0 ? aSampleNumber <= vDataLength : true))
    {
        double aSample = static_cast<double>(aSamples[vSignalNumber]);
        aSample -= mSignalInfo[vSignalNumber].adczero;
        aSample /= mSignalInfo[vSignalNumber].gain;
        aVector[aSampleNumber++] = aSample;
    }

    return aVector;
}

DataReader::DataReader(std::string vPath, std::string vRecordName, int vDataLength)
{
    mDataVectors.clear();
    setwfdb(const_cast<char*>(vPath.c_str()));
    if(isigopen(const_cast<char*>(vRecordName.c_str()), mSignalInfo, mSignalCount) < 1)
    {
        throw std::runtime_error("Cannot open record");
    }
    for(auto aIndex = 0; aIndex < mSignalCount; aIndex++)
    {
        mDataVectors.push_back(getSignal(aIndex, vDataLength));
    }
}

Eigen::VectorXd & DataReader::getData(std::size_t vSignalNumber)
{
    return mDataVectors[vSignalNumber];
}
