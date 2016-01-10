#pragma once


#include "Command.h"

extern "C"
{
    #include "DLLmain.h"
}


class DataBase
{
public:
    DataBase();

    // Return address for decompilation. If == -1, addresses not exists
    int NextAddress();

    void AddNewData(bool succsefull, int address, OutStruct *params);

    void CreateReport();

private:
    std::vector<Command> commands;
    std::vector<int> addressesForScan;

    void RemoveScanAddress(int address);
    void AddScanAddress(int address);
    bool AddressAlreadyScanOrFuture(int address);
    void WriteCommand(std::ofstream &file, Command &command);
    void WriteBinaryByte(std::ofstream &file, int value);
};
