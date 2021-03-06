///////////////////////////////////////////////////////////////////
// Computer Organization, this is a helper class I made 
// to help me go through JHU's Computer Organization 605.204.82
// Created by Tiger Shan
///////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <stack>
#include <vector>
#include <regex>
using namespace std;

namespace TSMipsHelper
{
	// this will tell what kind of instruction format we are going to use.
	enum InstructionType
	{
		R,
		I,
		J,
		FR,
		FI
	};

	static const string NumberIndex[16] = { "0", "1","2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };

	static bool ContainRegisterSign(std::string& s)
	{
		if (s.find('$') != std::string::npos)
			return true;
		
		return false;
	}

	// split spaces using regex
	static std::vector<std::string> Resplit(const std::string& s, std::string rgx_str = "\\s+") 
	{
		std::vector<std::string> elems;

		std::regex rgx(rgx_str);

		std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
		std::sregex_token_iterator end;

		while (iter != end) {
			//std::cout << "S43:" << *iter << std::endl;
			elems.push_back(*iter);
			++iter;
		}

		return elems;

	}
	
	// make it easy to string comparison by switch to all lower case
	static std::string make_lowercase(const std::string& in)
	{
		std::string out;

		std::transform(in.begin(), in.end(), std::back_inserter(out), ::tolower);
		return out;
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

		return 0;
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

		TsBinary()
		{
			BinaryData = "0000";
		}

		// input string of each char must be either 0 or 1 
		TsBinary(string BinaryString)
		{
			BinaryData = BinaryString;
		}

		void SetData(string InputString)
		{
			BinaryData = InputString;
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
					TempBinaryData[i] = '0';
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

			return TempBinaryData;
		}

		int ConvertToDecimal()
		{
			int sum = 0;

			for (string::size_type i = 0; i < BinaryData.size(); i++)
			{
				size_t Exponent = BinaryData.size() - 1 - i;

				sum += ConvertToInt(BinaryData[i]) *  pow(2, Exponent);
			}

			return sum;
		}

		string ConvertToHex()
		{
			int Decimal = ConvertToDecimal();

			return ConvertDecimalToHex(Decimal);
		}

		// this can cause over flow, we can store previous binary 
		// after trim data we can compare this binary with previous binary
		// if it's not the same number, then there is overflow when trim bits(missing 1s, so 0s infront should be ok)
		void TrimData(unsigned int length, bool signedExtension = false)
		{
			std::stack<char> StackBinary;

			char FirstChar = BinaryData[0];

			for (size_t i = BinaryData.size() -1 ; i > 0; i--)
			{
				StackBinary.push(BinaryData[i]);
			}

			if (StackBinary.size() > length)
			{
				BinaryData = "";

				for (unsigned int i = 0; i < length; i++)
				{
					BinaryData += StackBinary.top();
					StackBinary.pop();
				}
			}
			else
			{
				unsigned int needDigits = length - BinaryData.size(); 

				string TempData = "";

				for (int i = 0; i < needDigits; i++)
				{
					TempData += (signedExtension) ? FirstChar : '0';
				}

				BinaryData = TempData + BinaryData;
			}


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
				sum += ConvertToInt(HexData[i]) * pow(16, Exponent);
			}

			return sum;
		}

		string ConvertToBinary()
		{
			int Decimal = ConvertToDecimal();

			return ConvertDecimalToBinary(Decimal);
		}
	};

	// idea is to make an assembler and disasembler, so I don't have to look at green sheet all the time.
	// further I am thinking about using this to convert pusedo code into multiple instructions, long way to go for now.
	// all reference for mips found at https://inst.eecs.berkeley.edu/~cs61c/resources/MIPS_Green_Sheet.pdf
	class TsMipsAssemblerUtil 
	{
	public:
		std::vector<string>	DecodeString;

		TsMipsAssemblerUtil()
		{
			Clear();
		}

		// return true/false depending on decode format is correct or not and number of parameters filled.
		bool SetInput(string Input)
		{
			DecodeString = Resplit(Input);
			
			//for (int i = 0; i < DecodeString.size(); i++)
			//{
			//	std::cout << DecodeString[i] << endl;
			//}
			//

			DecodeOp(DecodeString[0]);

			//std::cout << CurrentType << OpCode.BinaryData << " func: " << FunctCode.BinaryData<< endl;
			if (CurrentType == InstructionType::R)
			{
				// make sure we arrange rs, rt, rd order
				// when we input code: it is like add $rd $rs $rt;
				// but when arrange in machine code binary: it is add $rs $rt $rd shamt functCode

				if (make_lowercase(DecodeString[0]) != "jr")
				{
					RD = DecodeRegister(DecodeString[1]);
					RD.TrimData(5);
				}
				//std::cout << RD.BinaryData << endl;

				if (make_lowercase(DecodeString[0]) != "jr")
				{
					RS = DecodeRegister(DecodeString[2]);
					RS.TrimData(5);
				}
				//cout << RS.BinaryData << endl;

				if (make_lowercase(DecodeString[0]) != "jr")
				{
					RT = DecodeRegister(DecodeString[3]);
					RT.TrimData(5);
				}

				//cout << RT.BinaryData << endl;
				if (make_lowercase(DecodeString[0]) == "jr")
				{
					RS = DecodeRegister(DecodeString[1]);
					RS.TrimData(5);
				}

				// TODO: haven't went through this in class yet
				Shamt = TsBinary("00000");

				if (RD.BinaryData == "" || RS.BinaryData == "" || RT.BinaryData == "")
					return false;

				std::cout << endl << " DEBUG INFO: " << endl;
				std::cout << " OPCode " << OpCode.BinaryData << endl;
				std::cout << " RS Decimal: " << RS.ConvertToDecimal() << " Binary: " << RS.BinaryData << endl;
				std::cout << " RT Decimal: " << RT.ConvertToDecimal() << " Binary: " << RT.BinaryData << endl;
				std::cout << " RD Decimal: " << RD.ConvertToDecimal() << " Binary: " << RD.BinaryData << endl;
				std::cout << " Shamt " << Shamt.BinaryData << endl;
				std::cout << " Funct HEX: " << FunctCode.ConvertToHex() << " Binary: " << FunctCode.BinaryData << endl;
				std::cout << endl;
				// function code should already be set.
			}

			// rt = rs + signextImm (2's complement)
			else if (CurrentType == InstructionType::I)
			{				
				string OpCodeString = make_lowercase(DecodeString[0]);

				if (OpCodeString == "addi" || OpCodeString == "addiu" || OpCodeString == "slti" || OpCodeString == "sltiu")
				{
					RS = DecodeRegister(DecodeString[2]);
					RS.TrimData(5);

					RT = DecodeRegister(DecodeString[1]);
					RT.TrimData(5);

					ImmediateValue = TsBinary(TsHex(DecodeString[3]).ConvertToBinary());

					// we need to sign extend
					ImmediateValue.TrimData(16, true);

					std::cout << endl << " DEBUG INFO: " << endl;
					std::cout << " OPCode " << OpCode.BinaryData << endl;
					std::cout << " RS Decimal: " << RS.ConvertToDecimal() << " Binary: " << RS.BinaryData << endl;
					std::cout << " RT Decimal: " << RT.ConvertToDecimal() << " Binary: " << RT.BinaryData << endl;
					std::cout << " Immediate Value: " << ImmediateValue.ConvertToHex() << " Binary: " << ImmediateValue.BinaryData << endl;
					std::cout << endl;
				}
				if (OpCodeString == "andi")
				{
					RS = DecodeRegister(DecodeString[2]);
					RS.TrimData(5);

					RT = DecodeRegister(DecodeString[1]);
					RT.TrimData(5);

					ImmediateValue = TsBinary(TsHex(DecodeString[3]).ConvertToBinary());

					// we need to zero extend
					ImmediateValue.TrimData(16);

					std::cout << endl << " DEBUG INFO: " << endl;
					std::cout << " OPCode " << OpCode.BinaryData << endl;
					std::cout << " RS Decimal: " << RS.ConvertToDecimal() << " Binary: " << RS.BinaryData << endl;
					std::cout << " RT Decimal: " << RT.ConvertToDecimal() << " Binary: " << RT.BinaryData << endl;
					std::cout << " Immediate Value: " << ImmediateValue.ConvertToHex() << " Binary: " << ImmediateValue.BinaryData << endl;
					std::cout << endl;
				}
			}
			// 
			else if (CurrentType == InstructionType::J)
			{
				string OpCodeString = make_lowercase(DecodeString[0]);

				if (OpCodeString == "j")
				{
					Address = TsBinary(TsHex(DecodeString[1]).ConvertToBinary());
					Address.TrimData(26);
				}
			}

			return true;
		}

		string GetBinary(bool isLittleIndian = true)
		{
			string Data = "";
			if (isLittleIndian)
			{
				if (CurrentType == InstructionType::R)
				{
					Data = OpCode.BinaryData + " " + RS.BinaryData + " " + RT.BinaryData + " " + RD.BinaryData + " " + Shamt.BinaryData + " " + FunctCode.BinaryData;
				}
				else if (CurrentType == InstructionType::I)
				{
					Data = OpCode.BinaryData + " " + RS.BinaryData + " " + RT.BinaryData + " " + ImmediateValue.BinaryData;
				}
				else if (CurrentType == InstructionType::J)
				{
					Data = OpCode.BinaryData + " " + Address.BinaryData;
				}
			}

			return Data;
		}

		string GetHex(bool isLittleIndian = true)
		{
			string Data = "";
			if (isLittleIndian)
			{
				if (CurrentType == InstructionType::R)
				{
					Data = OpCode.BinaryData + RS.BinaryData + RT.BinaryData + RD.BinaryData + Shamt.BinaryData + FunctCode.BinaryData;
					TsBinary binary = TsBinary(Data);
					Data = binary.ConvertToHex();
				}
				else if (CurrentType == InstructionType::I)
				{
					Data = OpCode.BinaryData + RS.BinaryData + RT.BinaryData + ImmediateValue.BinaryData;
					TsBinary binary = TsBinary(Data);
					Data = binary.ConvertToHex();
				}
				else if (CurrentType == InstructionType::J)
				{
					Data = OpCode.BinaryData + Address.BinaryData;
					TsBinary binary = TsBinary(Data);
					Data = binary.ConvertToHex();
				}
			}

			return Data;

		}

		// register should $ sign infront
		TsBinary DecodeRegister(string registerS)
		{
			string Data = "";

			if (!ContainRegisterSign(registerS))
				Data = "";
			
#pragma region temporary register
			if (make_lowercase(registerS) == "$t0")
			{
				Data = ConvertDecimalToBinary(8);
			}
			else if (make_lowercase(registerS) == "$t1")
			{
				Data = ConvertDecimalToBinary(9);
			}
			else if (make_lowercase(registerS) == "$t2")
			{
				Data = ConvertDecimalToBinary(10);
			}
			else if (make_lowercase(registerS) == "$t3")
			{
				Data = ConvertDecimalToBinary(11);
			}
			else if (make_lowercase(registerS) == "$t4")
			{
				Data = ConvertDecimalToBinary(12);
			}
			else if (make_lowercase(registerS) == "$t5")
			{
				Data = ConvertDecimalToBinary(13);
			}
			else if (make_lowercase(registerS) == "$t6")
			{
				Data = ConvertDecimalToBinary(14);
			}
			else if (make_lowercase(registerS) == "$t7")
			{
				Data = ConvertDecimalToBinary(15);
			}
			else if (make_lowercase(registerS) == "$t8")
			{
				Data = ConvertDecimalToBinary(24);
			}
			else if (make_lowercase(registerS) == "$t9")
			{
				Data = ConvertDecimalToBinary(25);
			}
#pragma endregion

#pragma region v register
			else if (make_lowercase(registerS) == "$v0")
			{
				Data = ConvertDecimalToBinary(2);
			}
			else if (make_lowercase(registerS) == "$v1")
			{
				Data = ConvertDecimalToBinary(3);
			}
#pragma endregion

#pragma region a register
			else if (make_lowercase(registerS) == "$a0")
			{
				Data = ConvertDecimalToBinary(4);
			}
			else if (make_lowercase(registerS) == "$a1")
			{
				Data = ConvertDecimalToBinary(5);
			}
			else if (make_lowercase(registerS) == "$a0")
			{
				Data = ConvertDecimalToBinary(6);
			}
			else if (make_lowercase(registerS) == "$a1")
			{
				Data = ConvertDecimalToBinary(7);
			}
#pragma endregion

#pragma region saved register
			else if (make_lowercase(registerS) == "$s0")
			{
				Data = ConvertDecimalToBinary(16);
			}
			else if (make_lowercase(registerS) == "$s1")
			{
				Data = ConvertDecimalToBinary(17);
			}
			else if (make_lowercase(registerS) == "$s2")
			{
				Data = ConvertDecimalToBinary(18);
			}
			else if (make_lowercase(registerS) == "$s3")
			{
				Data = ConvertDecimalToBinary(19);
			}
			else if (make_lowercase(registerS) == "$s4")
			{
				Data = ConvertDecimalToBinary(20);
			}
			else if (make_lowercase(registerS) == "$s5")
			{
				Data = ConvertDecimalToBinary(21);
			}
			else if (make_lowercase(registerS) == "$s6")
			{
				Data = ConvertDecimalToBinary(22);
			}
			else if (make_lowercase(registerS) == "$s7")
			{
				Data = ConvertDecimalToBinary(23);
			}
#pragma endregion
			
			else if (make_lowercase(registerS) == "$ra")
			{
				Data = ConvertDecimalToBinary(31);
			}
			else if (make_lowercase(registerS) == "$fp")
			{
				Data = ConvertDecimalToBinary(30);
			}
			else if (make_lowercase(registerS) == "$sp")
			{
			Data = ConvertDecimalToBinary(29);
			}
			else if (make_lowercase(registerS) == "$gp")
			{
			Data = ConvertDecimalToBinary(28);
			}

			return TsBinary(Data);

		}

		void DecodeOp(string op)
		{
#pragma region R region decode
			if (make_lowercase(op) == "add")
			{
				OpCode = TsBinary("000000");
				FunctCode = TsBinary(TsHex("20").ConvertToBinary());
				FunctCode.TrimData(6);
				CurrentType = InstructionType::R;
			}
			else if (make_lowercase(op) == "sub")
			{
				OpCode = TsBinary("000000");
				FunctCode = TsBinary(TsHex("22").ConvertToBinary());
				FunctCode.TrimData(6);
				CurrentType = InstructionType::R;
			}
			else if (make_lowercase(op) == "subu")
			{
				OpCode = TsBinary("000000");
				FunctCode = TsBinary(TsHex("23").ConvertToBinary());
				FunctCode.TrimData(6);
				CurrentType = InstructionType::R;
			}
			else if (make_lowercase(op) == "addu")
			{
				OpCode = TsBinary("000000");
				FunctCode = TsBinary(TsHex("21").ConvertToBinary());
				FunctCode.TrimData(6);
				CurrentType = InstructionType::R;
			}
			else if (make_lowercase(op) == "and")
			{
				OpCode = TsBinary("000000");
				FunctCode = TsBinary(TsHex("24").ConvertToBinary());
				FunctCode.TrimData(6);
				CurrentType = InstructionType::R;
			}
			else if (make_lowercase(op) == "jr")
			{
				OpCode = TsBinary("000000");
				FunctCode = TsBinary(TsHex("08").ConvertToBinary());
				RD.SetData("00000");
				RT.SetData("00000");

				FunctCode.TrimData(6);


				CurrentType = InstructionType::R;
			}
			else if (make_lowercase(op) == "nor")
			{
				OpCode = TsBinary("000000");
				FunctCode = TsBinary(TsHex("27").ConvertToBinary());
				FunctCode.TrimData(6);
				CurrentType = InstructionType::R;
			}
			else if (make_lowercase(op) == "or")
			{
				OpCode = TsBinary("000000");
				FunctCode = TsBinary(TsHex("25").ConvertToBinary());
				FunctCode.TrimData(6);
				CurrentType = InstructionType::R;
			}
			// still to encode : slt, sltu, sll, srl for R

#pragma endregion

#pragma region I region decode
			else if (make_lowercase(op) == "addi")
			{
				OpCode = TsBinary(TsHex("8").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "addiu")
			{
				OpCode = TsBinary(TsHex("9").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "andi")
			{
				OpCode = TsBinary(TsHex("C").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "beq")
			{
				OpCode = TsBinary(TsHex("4").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "bne")
			{
				OpCode = TsBinary(TsHex("5").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "lbu")
			{
				OpCode = TsBinary(TsHex("24").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "lhu")
			{
				OpCode = TsBinary(TsHex("25").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "ll")
			{
				OpCode = TsBinary(TsHex("30").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "lui")
			{
				OpCode = TsBinary(TsHex("F").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "lw")
			{
				OpCode = TsBinary(TsHex("23").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "ori")
			{
				OpCode = TsBinary(TsHex("D").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "slti")
			{
				OpCode = TsBinary(TsHex("A").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "sltiu")
			{
				OpCode = TsBinary(TsHex("B").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "sb")
			{
				OpCode = TsBinary(TsHex("28").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "sc")
			{
				OpCode = TsBinary(TsHex("38").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "sh")
			{
				OpCode = TsBinary(TsHex("29").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
			else if (make_lowercase(op) == "sw")
			{
				OpCode = TsBinary(TsHex("2B").ConvertToBinary());
				OpCode.TrimData(6);

				CurrentType = InstructionType::I;
			}
#pragma endregion

#pragma region J region decode
			else if (make_lowercase(op) == "j")
			{
				OpCode = TsBinary("000010");
				CurrentType = InstructionType::J;
			}
			else if (make_lowercase(op) == "jal")
			{
				OpCode = TsBinary("000011");
				CurrentType = InstructionType::J;
			}
#pragma endregion
		}

		// clear data
		void Clear()
		{
			OpCode = TsBinary();
			RS = TsBinary();
			RT = TsBinary();
			RD = TsBinary();
			FunctCode = TsBinary();
			Address = TsBinary();
			Shamt = TsBinary();
			ImmediateValue = TsBinary();

			CurrentType = InstructionType::R;
		}

	private:
		TsBinary OpCode; // for add, addi, jump etc.
		TsBinary RS;
		TsBinary RT;
		TsBinary RD;
		TsBinary FunctCode; // for distic same op but different functions
		TsBinary Address;
		TsBinary Shamt;
		TsBinary ImmediateValue; // this value is a two's complement for addi. 16 bit two's complement number, between -32769 and  32768

		InstructionType CurrentType;
	};
}