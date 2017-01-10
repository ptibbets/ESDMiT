#include <iostream>
#include "DataReader.h"
#include "DataWriter.h"

int main(int argc, char **argv)
{
    std::string aPath(argv[1]);
    std::string aRecord(argv[2]);

    try
    {
        DataReader aReader(aPath, aRecord);
        auto aSignals = aReader.getData();
        writeData("out.txt", aSignals);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
