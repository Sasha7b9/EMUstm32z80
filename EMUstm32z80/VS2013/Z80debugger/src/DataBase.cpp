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
    addressesForScan.push_back(8);
    addressesForScan.push_back(0x10);
    addressesForScan.push_back(0x18);
    addressesForScan.push_back(0x20);
    addressesForScan.push_back(0x28);
    addressesForScan.push_back(0x30);
    addressesForScan.push_back(0x38);

    addressesForScan.push_back(0x66);
    addressesForScan.push_back(0x03f8);
    addressesForScan.push_back(0x0425);
    addressesForScan.push_back(0x04c2);
    addressesForScan.push_back(0x04fe);
    addressesForScan.push_back(0x053f);
    addressesForScan.push_back(0x0556);
    addressesForScan.push_back(0x0605);
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
void DataBase::AddNewData(bool succsefull, int address, OutStruct *params)
{
    RemoveScanAddress(address);

    Command command;
    
    command.address = address;

    for(int i = 0; i < params->numOpCodes; i++)
    {
        command.opCodes.push_back(params->opCodes[i]);
    }

    if(succsefull)
    {
        command.numTackts = params->tackts;

        command.mnemonic = std::string(params->mnemonic);

        command.transcript = string(params->transcript);

        command.flags = string(params->flags);

        command.comment = string(params->comment);

        command.tackts = params->tackts;
    }
    else
    {
        command.bad = true;
    }

    if(command.address == 0x04d8)
    {
        command.address = command.address;
    }

    commands.push_back(command);

    if(succsefull)
    {
        for(int i = 0; i < params->numAddresses; i++)
        {
            AddScanAddress((int)params->addresses[i]);
        }
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DataBase::RemoveScanAddress(int address)
{
    for(int i = 0; i < (int)addressesForScan.size(); i++)
    {
        if(addressesForScan[(uint)i] == address)
        {
            if(address == 0x04d8)
            {
                address = address;
            }
            addressesForScan.erase(addressesForScan.begin() + i);

            if(address == 0x04d8)
            {
                address = address;
            }

            return;
        }
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DataBase::AddScanAddress(int address)
{
    if(address < 16384 && !AddressAlreadyScanOrFuture(address))
    {
        if(address == 0x04d8)
        {
            address = address;
        }
        addressesForScan.push_back(address);
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool DataBase::AddressAlreadyScanOrFuture(int address)
{
    if(address == 0x04d8)
    {
        address = address;
    }

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

    file << std::hex << std::setw(2) << std::setfill('0') << std::right << (int)command.opCodes[0] << " | ";
    WriteBinaryByte(file, (int)command.opCodes[0]);
    file << " | ";

    if(command.bad)
    {
        file << "ERROR!!! BAD COMMAND!!! ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    }
    else
    {
        file << std::setw(14) << std::left << std::setfill(' ') << command.mnemonic;
        /*
        if(!command.transcript.empty())
        {
            file << std::setw(20) << command.transcript << " | ";
        }
        else
        {
            file << "                     | ";
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
        */
        if(!command.comment.empty())
        {
            file << " | " <<  command.comment;
        }
    }

    for(uint i = 1; i < command.opCodes.size(); i++)
    {
        file << endl << "     | ";
        file << std::hex << std::setw(2) << std::setfill('0') << std::right << (int)command.opCodes[i] << " | ";
        WriteBinaryByte(file, (int)command.opCodes[i]);
        file << " |";
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
            if((addressNext - commands[i].address) > (int)commands[i].opCodes.size())
            {
                file << "--------------------------------------------------------------------------------------------------------------" << endl;
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


//------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<Command>& DataBase::GetCommands()
{
    return commands;
}