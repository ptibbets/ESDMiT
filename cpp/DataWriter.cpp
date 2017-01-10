#include "DataWriter.h"
#include <fstream>

void writeData(std::string vFilename, std::vector<Eigen::VectorXd>& vData) {
    std::fstream aFile(vFilename, std::ios::out);
    std::size_t aSignalsSize = vData[0].size();
    for (std::size_t i = 0; i < aSignalsSize; ++i) {
        for (auto& iSignal : vData) {
            aFile << iSignal[i] << "\t";
        }
        aFile << "\n";
    }
    aFile << std::endl;
}
