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

        command.tackts = tackts;
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
void DataBase::WriteBinaryByte(std::ofstream &file, int value)
{
    vector<int> bits;

    for(int i = 0; i < 8; i++)
    {
        bits.push_back(value % 2);
        value /= 2;
    }

    file << std::dec;

    file << bits[7];
    file << bits[6];
    file << " ";
    file << bits[5];
    file << bits[4];
    file << bits[3];
    file << " ";
    file << bits[2];
    file << bits[1];
    file << bits[0];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DataBase::WriteCommand(ofstream &file, Command &command)
{
    file << std::right << std::hex << std::setw(4) << std::setfill('0') << command.address << " | ";

   file << std::hex << (int)command.opCodes[0] << " | ";
   WriteBinaryByte(file, (int)command.opCodes[0]);
   file << " | ";

    if(command.bad)
    {
        file << "ERROR!!! BAD COMMAND!!! ERROR!!!";
    }
    else
    {
        file << std::setw(11) << std::left << std::setfill(' ') << command.mnemonic << " | ";
        if(!command.transcript.empty())
        {
            file << std::setw(16) << command.transcript << " | ";
        }
        else
        {
            file << "                 | ";
        }
        if(!command.flags.empty())
        {
            file << command.flags << " | ";
        }
        else
        {
            file << "         | ";
        }
        file << std::dec << std::setw(2) << command.tackts << " | ";
        if(!command.comment.empty())
        {
            file << command.comment;
        }

        for(uint i = 1; i < command.opCodes.size(); i++)
        {
            file << endl <<  "     | ";
            file << std::hex << (int)command.opCodes[i] << " | ";
            WriteBinaryByte(file, (int)command.opCodes[i]);
            file << " |";
        }
    }
    file << endl;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DataBase::CreateReport()
{
    std::sort(commands.begin(), commands.end());


    ofstream file;

    file.open("report.txt");

    for(size_t i = 0; i < commands.size(); i++)
    {
        WriteCommand(file, commands[i]);

        if(i < commands.size() - 1)
        {
            int addressNext = commands[i + 1].address;
            if((addressNext - commands[i].address) > commands[i].opCodes.size())
            {
                file << endl;
            }
        }
    }

    file << endl << endl << " ***** BAD ADDRESSES *****" << endl;

    for(size_t i = 0; i < commands.size(); i++)
    {
        if(commands[i].bad)
        {
            WriteCommand(file, commands[i]);
        }
    }

    file.close();
}
