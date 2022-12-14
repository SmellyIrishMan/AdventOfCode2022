#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day11.cpp"
#include <filesystem>
#include <fstream>
#include <regex>
#include <unordered_map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdventOfCode::Day11;

unsigned int GetLastNumberInString(const std::string& string)
{
	size_t onePastLastSpaceChar = string.find_last_of(' ') + 1;
	return std::stoul(string.substr(onePastLastSpaceChar, string.size() - onePastLastSpaceChar));
}

std::ifstream& operator>>(std::ifstream& stream, MonkeyData& monkeyData)
{
	std::regex digits{ R"(\D*(\d+))"};
	std::regex operationPattern{ R"((\+|\*) (old|\d*))" };
	std::string line;
	std::getline(stream, line);
	while (!line.empty())
	{
		std::smatch matches;
		while (!line.empty() && std::regex_search(line, matches, digits))
		{
			if(matches[1].length() > 0)
			{
				monkeyData.itemWorryValues.push_back(std::stoul(matches[1].str()));
			}
			line = matches.suffix().str(); // Proceed to the next match
		}
		//Get the operation. Get the operator value.
		//Make sure to handle the "old" case
		std::getline(stream, line);
		std::regex_search(line, matches, operationPattern);
		monkeyData.operation = matches[1] == '+' ? Operator::Add : Operator::Multiply;
		if (matches[2] == "old")
		{
			monkeyData.operation = Operator::Square;
		}
		else
		{
			monkeyData.operationValue = std::stoul(matches[2]);
		}

		std::getline(stream, line);
		monkeyData.divider = GetLastNumberInString(line);

		std::getline(stream, line);
		monkeyData.whereToThrow.first = static_cast<size_t>(GetLastNumberInString(line));
		
		std::getline(stream, line);
		monkeyData.whereToThrow.second = static_cast<size_t>(GetLastNumberInString(line));

		return stream;
	}

	return stream;
}

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day11Tests)
	{
	public:

		ListOfMonkeyData GetInputFromFile(std::string filepath)
		{
			ListOfMonkeyData monkeyList;
			std::filesystem::path inputPath{ filepath };

			std::unordered_map<std::string, Operator> charToOperatorType
			{
				{"+", Operator::Add},
				{"*", Operator::Multiply}
			};

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				std::string line;
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);

					std::smatch matches;
					std::regex regexPattern{ R"(Monkey)" };
					if (std::regex_search(line, matches, regexPattern))
					{
						MonkeyData data;
						fileInput >> data;
						monkeyList.push_back(data);
					}
				}
			}

			return monkeyList;
		}

		TEST_METHOD(Day11SampleTests)
		{
			ListOfMonkeyData data = GetInputFromFile("Data/Day11SampleInput.txt");
			//Assert::AreEqual(10'605ull, DetermineLevelOfMonkeyBusiness(data, 20, true));
			Assert::AreEqual(2'713'310'158ull, DetermineLevelOfMonkeyBusiness(data, 10'000, false));
		}

		TEST_METHOD(Day11ActualInputTest)
		{
			ListOfMonkeyData data = GetInputFromFile("Data/Day11Input.txt");
			Assert::AreEqual(54'752ull, DetermineLevelOfMonkeyBusiness(data, 20, true));
			Assert::AreEqual(54'752ull, DetermineLevelOfMonkeyBusiness(data, 10'000, false));
		}
	};
}