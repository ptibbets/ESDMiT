#include <iostream>
#include "DataReader.h"
#include "DataWriter.h"
#include "emd.h"

int main(int argc, char **argv)
{
    std::string aPath(argv[1]);
    std::string aRecord(argv[2]);

    try
    {
        DataReader aReader(aPath, aRecord, 250);
        auto aSignals = aReader.getData();
        auto aIMFs = emd(aSignals[0]);
        writeData("out.txt", aSignals);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
