#include "DataReader.h"

void DataReader::getSignals(int vDataLength)
{
    for(auto aIndex = 0; aIndex < mSignalCount; aIndex++)
    {
        Eigen::VectorXd aEigenVec((vDataLength >= 0) ? vDataLength : mSignalInfo[aIndex].nsamp);
        mDataVectors.push_back(aEigenVec);
    }
    int aSamples[WFDB_MAXSIG];
    int aSampleNumber = 0;
    while((getvec(aSamples) >= 0) && (vDataLength >= 0) ? aSampleNumber < vDataLength : true)
    {
        for(auto aIndex = 0; aIndex < (int)mDataVectors.size(); aIndex++)
        {
            double aSample = static_cast<double>(aSamples[aIndex]);
            aSample -= mSignalInfo[aIndex].adczero;
            aSample /= mSignalInfo[aIndex].gain;
            mDataVectors[aIndex][aSampleNumber] = aSample;
        }
        aSampleNumber++;
    }
}

DataReader::DataReader(std::string vPath, std::string vRecordName, int vDataLength)
{
    mDataVectors.clear();
    setwfdb(const_cast<char*>(vPath.c_str()));
    if(isigopen(const_cast<char*>(vRecordName.c_str()), mSignalInfo, mSignalCount) < 1)
    {
        throw std::runtime_error("Cannot open record");
    }
    getSignals(vDataLength);
}

std::vector<Eigen::VectorXd> & DataReader::getData()
{
    return mDataVectors;
}
