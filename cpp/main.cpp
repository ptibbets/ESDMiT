#include <iostream>
#include "DataReader.h"
#include "DataWriter.h"
#include "emd.h"
#include "filter.h"
#include <chrono>

int main(int argc, char **argv)
{
    std::string aPath(argv[1]);
    std::string aRecord(argv[2]);

    try
    {
        DataReader aReader(aPath, aRecord, std::stoi(std::string(argv[3])));
        auto aSignals = aReader.getData();
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        auto aIMFs = emd(aSignals[0]);
        auto aResult = filter(aIMFs, 2);
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "Time: " << duration << std::endl;
        std::vector<decltype(aResult)> aResultVec;
        aResultVec.push_back(aResult);
        writeMatrix("../imfs.mat", aIMFs);
        writeMatrix("../out.mat", aResultVec);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
