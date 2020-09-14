///////////////////////////////////////////////////////////////////
// Computer Organization, this is a helper class I made 
// to help me go through JHU's Computer Organization 605.204.82
// Created by Shan WenQin
///////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <stack>
using namespace std;

namespace TSMipsHelper
{
	static const string NumberIndex[16] = { "0", "1","2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };

	// we could just use stoi base hex but we want to keep it as string for easier manipulation
	static string ConvertDecimalToBinary(int Decimal)
	{
		std::stack<string> StackOutput;

		ConvertDecimalToBase(Decimal, 2, StackOutput);

		string output = "";

		while (StackOutput.size() > 0)
		{
			output += StackOutput.top();

			StackOutput.pop();
		}

		return output;
	}

	// we could just use stoi base hex but we want to keep it as string for easier manipulation
	static string ConvertDecimalToHex(int Decimal)
	{
		std::stack<string> StackOutput;

		ConvertDecimalToBase(Decimal, 16, StackOutput);

		string output = "";

		while (StackOutput.size() > 0)
		{
			output += StackOutput.top();

			StackOutput.pop();
		}

		return output;

	}

	// this would only work for whole number, decimal should not use stack
	static void ConvertDecimalToBase(int Number, int Base, std::stack<string>& Output)
	{
		if (Number < Base)
		{
			Output.push(NumberIndex[Number % Base]);

			return;
		}

		int Quo = Number / Base;

		int Remainder = Number - Quo * Base;

		// add remainder
		Output.push(NumberIndex[Remainder]);

		ConvertDecimalToBase(Quo, Base, Output);
	}

	// convert to decimal, base 10, TODO: make better conversion algorithm, go through numberIndex, and then XOR until == 0?
	// forgive me for my inexperince here, but for quick conversion i don't want to think too much, save time.
	static int ConvertToInt(char symbol)
	{
		if (symbol == '0')
			return 0;
		else if (symbol == '1')
			return 1;
		else if (symbol == '2')
			return 2;
		else if (symbol == '3')
			return 3;
		else if (symbol == '4')
			return 4;
		else if (symbol == '5')
			return 5;
		else if (symbol == '6')
			return 6;
		else if (symbol == '7')
			return 7;
		else if (symbol == '8')
			return 8;
		else if (symbol == '9')
			return 9;
		else if (symbol == 'A')
			return 10;
		else if (symbol == 'B')
			return 11;
		else if (symbol == 'C')
			return 12;
		else if (symbol == 'D')
			return 13;
		else if (symbol == 'E')
			return 14;
		else if (symbol == 'F')
			return 15;
	}

	// Todo
	static string AddToBinaryString(string Binary1, string Binary2)
	{
		// make sure their length is the  same, if not, populate 0's infront for the less binarylength

		

		// 2. add them
	}


	struct TsBinary
	{
	public:

		string BinaryData;

		// input string of each char must be either 0 or 1 
		TsBinary(string BinaryString)
		{
			BinaryData = BinaryString;
		}

		string ConvertTwosComplement()
		{
			// take all the binary data switch 0 to 1 and switch 1 to zero

			string TempBinaryData = BinaryData;


			// 1's complement
			for (string::size_type i = 0; i < TempBinaryData.size(); i++)
			{
				if (TempBinaryData[i] == '0')
					TempBinaryData[i] = '1';
				else if (TempBinaryData[i] == '1')
					TempBinaryData[i] = '2';
			}

			// add one bit
			for (string::size_type i = TempBinaryData.size(); i > 0; i--)
			{
				if (TempBinaryData[i] == '0')
				{
					TempBinaryData[i] = '1';
					break;
				}
				else if(TempBinaryData[i] == '1')
				{
					TempBinaryData[i] = '0';
					//continue means we assume there is a carry
					continue;
				}

			}

		}

		int ConvertToDecimal()
		{
			int sum = 0;

			for (string::size_type i = 0; i < BinaryData.size(); i++)
			{
				size_t Exponent = BinaryData.size() - 1 - i;

				sum += ConvertToInt(BinaryData[Exponent]) +  pow(2, Exponent);
			}

			return sum;
		}

		string ConvertToHex()
		{
			int Decimal = ConvertToDecimal();

			return ConvertDecimalToHex(Decimal);
		}

	};


	struct TsHex
	{

	public:
		string HexData;

		// input string of each char must be either 0 or 1 
		TsHex(string HexString)
		{
			HexData = HexString;
		}

		int ConvertToDecimal()
		{
			int sum = 0;

			for (string::size_type i = 0; i < HexData.size(); i++)
			{
				size_t Exponent = HexData.size() - 1 - i;
				sum += ConvertToInt(HexData[Exponent]) + pow(16, Exponent);
			}

			return sum;
		}

		string ConvertToBinary()
		{
			int Decimal = ConvertToDecimal();

			return ConvertDecimalToBinary(Decimal);
		}

	};

	class TsMipsUtil
	{
	public:

		TsMipsUtil(){}

	};
}