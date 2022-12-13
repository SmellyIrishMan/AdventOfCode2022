#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day10.cpp"
#include <filesystem>
#include <fstream>
#include <regex>
#include <unordered_map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdventOfCode::Day10;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day10Tests)
	{
	public:

		ListOfInstructions GetInputFromFile(std::string filepath)
		{
			ListOfInstructions instructions;
			std::filesystem::path inputPath{ filepath };

			std::unordered_map<std::string, InstructionType> stringToInstructionType
			{
				{"noop", InstructionType::NoOp},
				{"addx", InstructionType::AddX}
			};

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				std::string line;
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);

					std::smatch matches;
					std::regex regexPattern{ R"((\w*)( )?(-?\d*))" };
					if (std::regex_search(line, matches, regexPattern))
					{
						Instruction instruction;
						instruction.type = stringToInstructionType[matches[1].str()];
						if (!matches[3].str().empty())
						{
							instruction.data = std::stoi(matches[3].str());
						}
						instructions.push_back(instruction);
					}
				}
			}

			return instructions;
		}

		TEST_METHOD(Day10SimpleTest)
		{
			ListOfInstructions instructions = GetInputFromFile("Data/Day10SimpleInput.txt");
			Assert::AreEqual(0, CombineSignalStrength(instructions));
		}
		TEST_METHOD(Day10SampleTests)
		{
			ListOfInstructions instructions = GetInputFromFile("Data/Day10SampleInput.txt");
			Assert::AreEqual(13'140, CombineSignalStrength(instructions));
		}

		TEST_METHOD(Day10ActualInputTest)
		{
			ListOfInstructions instructions = GetInputFromFile("Data/Day10Input.txt");
			Assert::AreEqual(11'780, CombineSignalStrength(instructions));
		}
	};
}