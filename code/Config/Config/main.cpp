

#include <iostream>
#include "ConfigBase.h"


int main(int argc, char** argv)
{
    std::string filePath = "D:\\service.conf";
    ConfigBase * config = new ConfigBase(filePath);

    config->LoadConfig();

    system("pause");
    return 0;
}