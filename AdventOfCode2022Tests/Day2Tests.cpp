#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day2.cpp"
#include <filesystem>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day2Tests)
	{
	public:

		TEST_METHOD(Day2SampleTests)
		{
			std::vector<AdventOfCode::RockPaperScissorsTurn> Turns = { {0, 1}, {1, 0}, {2, 2} };
			unsigned int result = AdventOfCode::Day2RockPaperScissorsStrategyGuide(Turns);
			Assert::AreEqual(15u, result);

			result = AdventOfCode::Day2RockPaperScissorsStrategyGuideUnlocked(Turns);
			Assert::AreEqual(12u, result);
		}

		TEST_METHOD(Day2ActualInputTest)
		{
			unsigned int part1Result = 0;
			unsigned int part2Result = 0;

			std::filesystem::path inputPath{ "Data/Day2Input.txt" };

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				std::vector<AdventOfCode::RockPaperScissorsTurn> turns;
				std::string line;
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);
					unsigned int player1Move = line[0] - 'A';
					unsigned int player2Move = line[2] - 'X';
					turns.emplace_back(player1Move, player2Move);
				}

				part1Result = AdventOfCode::Day2RockPaperScissorsStrategyGuide(turns);
				part2Result = AdventOfCode::Day2RockPaperScissorsStrategyGuideUnlocked(turns);
			}

			Assert::AreEqual(14'297u, part1Result);
			Assert::AreEqual(10'498u, part2Result);
		}
	};
}
