#pragma once


#include "Command.h"


class DataBase
{
public:
    DataBase();

    // Return address for decompilation. If == -1, addresses not exists
    int NextAddress();

    void AddNewData(bool succsefull, int address, char mnemonic[100], char comment[100], char flags[100], char transcript[100],
                    uint16 addresses[10], int numAddresses, uint8 opCodes[10], int numOpCodes, int tackts);

    void CreateReport();

private:
    std::vector<Command> commands;
    std::vector<int> addressesForScan;

    void RemoveScanAddress(int address);
    void AddScanAddress(int address);
    bool AddressAlreadyScanOrFuture(int address);
    void WriteCommand(std::ofstream &file, Command &command);
};
