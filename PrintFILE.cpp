#include "PrintFILE.h"

#include <iostream>
#include <fstream>

void PrintFILE::createFile(std::string listName)
{
    std::string fileName = "SGH_" + listName + ".txt";
    std::ofstream file{ fileName };
    file.close();
}

void PrintFILE::writeList(std::string listName,
    std::string uppgradeNameArray[200][20], int uppgradeCostArray[200][20],
    int uppgradeNrArray[20], int unitFigerCount[200], int unitCost[200],
    static char unitName[200][32], static char unitNote[200][255 * 6], int unitNr)
{
    std::fstream file;
    std::string fileName = "SGH_" + listName + ".txt";
    file.open(fileName);
    file << "          " << listName << std::endl;

    int TootlOfAll = 0;

    for (int row = 0; row < unitNr; row++)
    {
        int tootaltNrOfFigur = unitFigerCount[row] * unitCost[row];
        file << "unit:" << unitName[row] << std::endl;
        int countSmpl = unitFigerCount[row], costSmpl = unitCost[row];
        file << "Figur Count: " << countSmpl;
        // file.seekg(-32, std::ios::cur); file.seekg(36, std::ios::cur);
        file << "|coset of figur: " << costSmpl << " | tootle: " << tootaltNrOfFigur << std::endl;

        int lodeSpot = uppgradeNrArray[row];
        for (short int i = 0; i < lodeSpot; i++)
        {
            file << uppgradeNameArray[row][i];
            int NameLong = std::size(uppgradeNameArray[row][i]);
            file.seekg(-NameLong, std::ios::cur); file.seekg(27, std::ios::cur);
            file << "-> " << uppgradeCostArray[row][i] << std::endl;
        }

        file << unitNote[row] << std::endl;

        int TootleUppgradeCost_ = 0;
        for (int i = 0; i < 19; i++)
        {
            TootleUppgradeCost_ = TootleUppgradeCost_ + uppgradeCostArray[row][i];
        }

        int tootalCostOfUnit = unitFigerCount[row] * unitCost[row] + TootleUppgradeCost_;
        TootlOfAll = TootlOfAll + tootalCostOfUnit;
        file << "Tootal cost: " << tootalCostOfUnit << "\n" << std::endl;
    }
    file << "List cost: ";
    file << TootlOfAll;
    file.close();
}