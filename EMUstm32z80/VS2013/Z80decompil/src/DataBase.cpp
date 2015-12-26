#include "stdafx.h"
#include "DataBase.h"


using std::ofstream;
using std::string;
using std::vector;
using std::endl;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DataBase::DataBase()
{
    addressesForScan.push_back(0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int DataBase::NextAddress()
{
    if(addressesForScan.size() > 0)
    {
        return addressesForScan[0];
    }
    return -1;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DataBase::AddNewData(bool succsefull, int address, char mnemonic[100], char comment[100], char flags[100], char transcript[100], uint16 addresses[10],
                          int numAddresses, uint8 opCodes[10], int numOpCodes, int tackts)
{
    RemoveScanAddress(address);

    Command command;
    
    command.address = address;

    for(int i = 0; i < numOpCodes; i++)
    {
        command.opCodes.push_back(opCodes[i]);
    }

    if(succsefull)
    {
        command.numTackts = tackts;

        command.mnemonic = std::string(mnemonic);

        for(int i = 0; i < numAddresses; i++)
        {
            AddScanAddress(addresses[i]);
        }

        command.transcript = string(transcript);

        command.flags = string(flags);

        command.comment = string(comment);
    }
    else
    {
        command.bad = true;
    }

    commands.push_back(command);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DataBase::RemoveScanAddress(int address)
{
    for(int i = 0; i < (int)addressesForScan.size(); i++)
    {
        if(addressesForScan[(uint)i] == address)
        {
            addressesForScan.erase(addressesForScan.begin() + i);
            return;
        }
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DataBase::AddScanAddress(int address)
{
    if(!AddressAlreadyScanOrFuture(address))
    {
        addressesForScan.push_back(address);
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool DataBase::AddressAlreadyScanOrFuture(int address)
{
    for each (auto &command in commands)
    {
        if(command.address == address)
        {
            return true;
        }
    }

    for each(auto addr in addressesForScan)
    {
        if(addr == address)
        {
            return true;
        }
    }

    return false;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DataBase::WriteCommand(ofstream &file, Command &command)
{
    file << command.address << " ";

    for(size_t n = 0; commands[n].opCodes.size(); n++)
    {
        file << std::hex << command.opCodes[n] << " ";
    }

    if(command.bad)
    {
        file << "ERROR!!! BAD COMMAND!!! ERROR!!!";
    }
    else
    {
        file << command.mnemonic;
    }

    file << endl;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DataBase::CreateReport()
{
    std::sort(commands.begin(), commands.end());


    ofstream file;

    file.open("report.txt");

    vector<int> badAdddresses;

    for(size_t i = 0; i < commands.size(); i++)
    {
        WriteCommand(file, commands[i]);
    }


    file << endl << endl;

    file << " ***** BAD ADDRESSES *****" << endl;

    for(size_t i = 0; i < commands.size(); i++)
    {
        if(commands[i].bad)
        {
            WriteCommand(file, commands[i]);
        }
    }

    file.close();
}
