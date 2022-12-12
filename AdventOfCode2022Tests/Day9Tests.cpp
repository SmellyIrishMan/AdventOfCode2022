#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day9.cpp"
#include <filesystem>
#include <fstream>
#include <regex>
#include <unordered_map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdventOfCode::Day9;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day9Tests)
	{
	public:

		TEST_METHOD(Day9SampleTests)
		{

			ListOfMoves input{ 
			{ AdventOfCode::DirectionRight, 4},
			{ AdventOfCode::DirectionUp, 4 },
			{ AdventOfCode::DirectionLeft, 3 },
			{ AdventOfCode::DirectionDown, 1 },
			{ AdventOfCode::DirectionRight, 4 },
			{ AdventOfCode::DirectionDown, 1 },
			{ AdventOfCode::DirectionLeft, 5 },
			{ AdventOfCode::DirectionRight, 2 } };

			Assert::AreEqual(13u, CountUniqueTailPositions(input, 2));
		}

		TEST_METHOD(Day9Sample2)
		{

			ListOfMoves input{
				{ AdventOfCode::DirectionRight, 5},
				{ AdventOfCode::DirectionUp, 8 },
				{ AdventOfCode::DirectionLeft, 8 },
				{ AdventOfCode::DirectionDown, 3 },
				{ AdventOfCode::DirectionRight, 17 },
				{ AdventOfCode::DirectionDown, 10 },
				{ AdventOfCode::DirectionLeft, 25 },
				{ AdventOfCode::DirectionUp, 20 } 
			};

			Assert::AreEqual(36u, CountUniqueTailPositions(input, 10));
		}

		TEST_METHOD(Day9ActualInputTest)
		{
			ListOfMoves moves;
			std::filesystem::path inputPath{ "Data/Day9Input.txt" };

			std::unordered_map<char, AdventOfCode::Direction2D> directionMap
			{
				{'U', AdventOfCode::DirectionUp },
				{'D', AdventOfCode::DirectionDown },
				{'R', AdventOfCode::DirectionRight },
				{'L', AdventOfCode::DirectionLeft }
			};

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				std::string line;
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);

					std::smatch matches;
					std::regex regexPattern{ R"((.) (\d*))" };
					if (std::regex_search(line, matches, regexPattern))
					{
						AdventOfCode::Direction2D direction = directionMap[matches[1].str()[0]];
						unsigned int steps = std::stoul(matches[2].str());
						Move move{ direction, steps };
						moves.push_back(move);
					}
				}
			}

			Assert::AreEqual(6'209u, CountUniqueTailPositions(moves, 2));
			Assert::AreEqual(2'460u, CountUniqueTailPositions(moves, 10));
		}
	};
}