#include <iostream>
#include "DataReader.h"

int main(int argc, char **argv)
{
    std::string aPath(argv[1]);
    std::string aRecord(argv[2]);

    try
    {
        DataReader aReader(aPath, aRecord);
        auto aSig = aReader.getData(0);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
