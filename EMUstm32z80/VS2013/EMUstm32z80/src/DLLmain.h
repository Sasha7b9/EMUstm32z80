#pragma once


__declspec(dllexport) void Init
(
    unsigned char RAM[65535],
    char mnemonic[100],
    char comment[100],
    char flags[100],
    char transcript[100],
    unsigned short addresses[10],
    int *numAddresses,
    unsigned char opCodes[10],
    int *numOpCodes,
    int tackts[1]
);

__declspec(dllexport) void Decode(unsigned short address);
