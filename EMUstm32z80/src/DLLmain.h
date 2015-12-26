#pragma once


typedef unsigned char uint8;
typedef unsigned short uint16;


__declspec(dllexport) void Init
(
    uint8 RAM[65535],
    char mnemonic[100],
    char comment[100],
    char flags[100],
    char transcript[100],
    uint16 addresses[10],
    int *numAddresses,
    uint8 opCodes[10],
    int tackts[1]
);

__declspec(dllexport) void Decode(uint16 address);
