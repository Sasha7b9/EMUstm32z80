#pragma once


class DataBase
{
public:
    int NextAddress();  // Return address for decompilation. If == 1, addresses not exists

    void AddNewData(char mnemonic[100], char comment[100], char flags[100], char transcript[100],
                    uint16 addresses[10], int numAddresses, uint8 opCodes[10], int numOpCodes, int tackts);

    void AddErrorAddress(int address);

private:
    std::vector<int> badAddresses;
};
