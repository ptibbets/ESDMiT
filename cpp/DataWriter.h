#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <Eigen/Eigen>
#include <matio.h>

template<typename tSignals>
bool writeData(std::string vFilename, tSignals& vData) {
    std::fstream aFile(vFilename, std::ios::out);
    aFile.close();
    auto mat = Mat_Open(vFilename.c_str(), MAT_ACC_RDWR);
    if (mat) {
        int i = 1;
        for (auto& vec : vData) {
            std::size_t dims[2] = { 1, (std::size_t)vec.size() };
            std::string name = "vec" + std::to_string(i++);
            auto matvar = Mat_VarCreate(name.c_str(), MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dims, (void*)vec.data(), 0);
            Mat_VarWrite(mat, matvar, MAT_COMPRESSION_NONE);
            Mat_VarFree(matvar);
        }
        Mat_Close(mat);
        return true;
    }
    return false;
}
