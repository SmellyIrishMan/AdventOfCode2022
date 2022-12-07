#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day5.cpp"
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day5Tests)
	{
	public:

		TEST_METHOD(Day5SampleTests)
		{
			AdventOfCode::Day5::Stacks initialStacks = {
				{'Z', 'N'},
				{'M', 'C', 'D'},
				{'P'}
			};

			AdventOfCode::Day5::StackMoves moves =
			{
				{1, 1, 0},
				{3, 0, 2},
				{2, 1, 0},
				{1, 0, 1},
			};
			std::string result = AdventOfCode::Day5ArrangeStacks(initialStacks, moves, AdventOfCode::Day5::CraneOrdering::ReverseOrder);
			Assert::AreEqual(std::string("CMZ"), result);

			std::string result2 = AdventOfCode::Day5ArrangeStacks(initialStacks, moves, AdventOfCode::Day5::CraneOrdering::KeepOrder);
			Assert::AreEqual(std::string("MCD"), result2);
		}

		TEST_METHOD(Day5ActualInputTest)
		{
			std::string part1Result;
			std::string part2Result;

			std::filesystem::path inputPath{ "Data/Day5Input.txt" };

			AdventOfCode::Day5::Stacks initialStacks = {
				{'B', 'Q', 'C'},
				{'R', 'Q', 'W', 'Z'},
				{'B', 'M', 'R', 'L', 'V'},
				{'C', 'Z', 'H', 'V', 'T', 'W'},
				{'D', 'Z', 'H', 'B', 'N', 'V', 'G'},
				{'H', 'N', 'P', 'C', 'J', 'F', 'V', 'Q'},
				{'D', 'G', 'T', 'R', 'W', 'Z', 'S'},
				{'C', 'G', 'M', 'N', 'B', 'W', 'Z', 'P'},
				{'N', 'J', 'B', 'M', 'W', 'Q', 'F', 'P'},
			};

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				AdventOfCode::Day5::StackMoves moves;
				std::string line;
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);

					std::smatch matches;
					std::regex regexPattern{ R"(move (\d*) from (\d*) to (\d*))" };
					if (std::regex_search(line, matches, regexPattern))
					{
						AdventOfCode::Day5::StackMove move(std::stoul(matches[1].str()), std::stoul(matches[2].str()) - 1, std::stoul(matches[3].str()) - 1);
						moves.push_back(move);
					}
				}

				part1Result = AdventOfCode::Day5ArrangeStacks(initialStacks, moves, AdventOfCode::Day5::CraneOrdering::ReverseOrder);
				part2Result = AdventOfCode::Day5ArrangeStacks(initialStacks, moves, AdventOfCode::Day5::CraneOrdering::KeepOrder);
			}

			Assert::AreEqual(std::string("BWNCQRMDB"), part1Result);
			Assert::AreEqual(std::string("NHWZCBNBF"), part2Result);
		}
	};
}