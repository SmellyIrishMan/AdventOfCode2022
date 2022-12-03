#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/AdventOfCode2022.cpp"
#include <filesystem>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(AdventOfCode2022Tests)
	{
	public:		
		TEST_METHOD(Day1Tests)
		{
			int64_t result = AdventOfCode::Day1HowManyCaloriesPerElf({ {1'000, 2'000, 3'000}, {4'000}, {5'000, 6'000}, {7'000, 8'000, 9'000}, {10'000} });
			Assert::AreEqual(int64_t(24'000), result);

			result = AdventOfCode::Day1HowManyCaloriesPerElf({ {1}, {0}, {0}, {0}, {1} });
			Assert::AreEqual(int64_t(1), result);

			result = AdventOfCode::Day1HowManyCaloriesPerElf({ {1}, {2}, {3}, {4}, {5} });
			Assert::AreEqual(int64_t(5), result);

			result = AdventOfCode::Day1HowManyCaloriesPerElf({ {1, 2, 3, 4}, {0, 0, 0, 0, 0, 0, 0, 0}, {3}, {4}, {5, 4, 3, 2, 1, 0} });
			Assert::AreEqual(int64_t(15), result);
		}

		TEST_METHOD(Day1Part2Tests)
		{
			int64_t result = AdventOfCode::Day1HowManyCaloriesAmongTopThreeElfs({ {1'000, 2'000, 3'000}, {4'000}, {5'000, 6'000}, {7'000, 8'000, 9'000}, {10'000} });
			Assert::AreEqual(int64_t(45'000), result);

			result = AdventOfCode::Day1HowManyCaloriesAmongTopThreeElfs({ {1'000, 2'000, 3'000} });
			Assert::AreEqual(int64_t(6'000), result);

			result = AdventOfCode::Day1HowManyCaloriesAmongTopThreeElfs({ {1'000, 2'000, 3'000}, {4'000} });
			Assert::AreEqual(int64_t(10'000), result);

			result = AdventOfCode::Day1HowManyCaloriesAmongTopThreeElfs({ });
			Assert::AreEqual(int64_t(0), result);
		}

		TEST_METHOD(Day1ActualInputTest)
		{
			int64_t part1Result = 0;
			int64_t part2Result = 0;

			std::filesystem::path inputPath{ "Data/Day1Input.txt" };

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				AdventOfCode::ElfCalorieList currentList;
				AdventOfCode::ElfCalorieLists allElfsLists;
				std::string line;
				while(!fileInput.eof())
				{
					std::getline(fileInput, line);
					if (line.empty())
					{
						allElfsLists.push_back(std::move(currentList));
						currentList = AdventOfCode::ElfCalorieList();
					}
					else
					{
						currentList.push_back(std::stoul(line));
					}
				}

				part1Result = AdventOfCode::Day1HowManyCaloriesPerElf(allElfsLists);
				part2Result = AdventOfCode::Day1HowManyCaloriesAmongTopThreeElfs(allElfsLists);
			}
			
			Assert::AreEqual(int64_t(69'310), part1Result);
			Assert::AreEqual(int64_t(206'104), part2Result);
		}

		TEST_METHOD(Day2Tests)
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
