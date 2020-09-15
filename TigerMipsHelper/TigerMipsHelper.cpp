// TigerMipsHelper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TsMipsHelper.h"

int main()
{
    //TSMipsHelper::TsBinary Data = TSMipsHelper::TsBinary("11000");

    //int ConvertedDecimal = Data.ConvertToDecimal();

    //std::cout << "Conversion Example: " << endl;
    //std::cout << Data.BinaryData << " Converted Decimal: " << ConvertedDecimal << " 2's Complement: " << Data.ConvertTwosComplement() << " HEX: " << Data.ConvertToHex() << endl << endl;
    string InputString = "add $v0 $a0 $v0";

    std::cout << "Input Instruction: " << InputString << endl;
    
    TSMipsHelper::TsMipsAssemblerUtil MipsAssembler = TSMipsHelper::TsMipsAssemblerUtil();

    MipsAssembler.SetInput(InputString);

    TSMipsHelper::TsBinary Answer = TSMipsHelper::TsBinary(MipsAssembler.GetBinary());
           
    // TODO: ConvertToHex() currently not working correctly
    std::cout << "Assembler machine code(Binary): " << MipsAssembler.GetBinary() << " HEX: " << Answer.ConvertToHex() << endl;
}