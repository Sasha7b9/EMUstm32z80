#pragma once


class Command
{
public:
    bool bad = false;
    int address = 0;
    std::vector<uint8> opCodes;
    std::string mnemonic;
    int numTackts = 0;
    std::string transcript;
    std::string flags;
    std::string comment;

    bool operator<(const Command &first);
};
