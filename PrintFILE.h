#pragma once

#include <iostream>
#include <fstream>

class PrintFILE
{
public:

    void createFile(std::string listName);

    void writeList(std::string listName,
        std::string uppgradeNameArray[200][20], int uppgradeCostArray[200][20],
        int uppgradeNrArray[20], int unitFigerCount[200], int unitCost[200],
        static char unitName[200][32], static char unitNote[200][255 * 6], int unitNr);
};

