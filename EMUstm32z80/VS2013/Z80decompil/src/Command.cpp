#include "stdafx.h"


#include "Command.h"


bool Command::operator<(const Command &first)
{
    return address < first.address;
};
