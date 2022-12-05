#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day3.cpp"
#include <filesystem>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day3Tests)
	{
	public:

		TEST_METHOD(Day3SampleTests)
		{
			AdventOfCode::BackpackList backpacks = { "vJrwpWtwJgWrhcsFMMfFFhFp", "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL", "PmmdzqPrVvPwwTWBwg", "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn", "ttgJtRGJQctTZtZT", "CrZsJsPPZsGzwwsLwLmpwMDw"};
			unsigned int result = AdventOfCode::Day3MisplacedItem(backpacks);
			Assert::AreEqual(157u, result);

			AdventOfCode::BackpackList firstTriplet = { "vJrwpWtwJgWrhcsFMMfFFhFp", "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL", "PmmdzqPrVvPwwTWBwg" };
			AdventOfCode::BackpackList secondTriplet = { "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn", "ttgJtRGJQctTZtZT", "CrZsJsPPZsGzwwsLwLmpwMDw" };
			Assert::AreEqual(70u, AdventOfCode::Day3TripletBadgeAssignment(firstTriplet) + AdventOfCode::Day3TripletBadgeAssignment(secondTriplet));
		}

		TEST_METHOD(Day3ActualInputTest)
		{
			unsigned int part1Result = 0;
			unsigned int part2Result = 0;

			std::filesystem::path inputPath{ "Data/Day3Input.txt" };

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				AdventOfCode::BackpackList backpacks;
				AdventOfCode::BackpackList backpackTriplets;
				std::string line;
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);
					backpacks.emplace_back(line);
					backpackTriplets.emplace_back(line);
					if (backpackTriplets.size() == 3)
					{
						part2Result += AdventOfCode::Day3TripletBadgeAssignment(backpackTriplets);
						backpackTriplets.clear();
					}
				}

				part1Result = AdventOfCode::Day3MisplacedItem(backpacks);

			}

			Assert::AreEqual(7'701u, part1Result);
			Assert::AreEqual(2'644u, part2Result);
		}
	};
}
