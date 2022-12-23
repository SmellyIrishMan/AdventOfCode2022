#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day12.cpp"
#include "../AdventOfCode2022/Utilities.h"
#include <filesystem>
#include <fstream>
#include <regex>
#include <iterator>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdventOfCode::Day12;

std::ifstream& operator>>(std::ifstream& stream, MapData& data)
{
	std::string line;
	while (!stream.eof())
	{
		std::getline(stream, line);
		std::vector<char> chars{ line.begin(), line.end() };
		data.heightmap.push_back(chars);

		size_t row = data.heightmap.size() - 1;
		for (size_t col = 0; col < chars.size(); col++)
		{
			if (chars[col] == 'S')
			{
				data.startingLocation = { row, col };
			}
			else if (chars[col] == 'a')
			{
				data.potentialStartingLocations.push_back({ row, col });
			}
		}
	}
	return stream;
}

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day12Tests)
	{
	public:

		MapData GetInputFromFile(std::string filepath)
		{
			MapData mapData;
			std::filesystem::path inputPath{ filepath };
			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				fileInput >> mapData;
			}

			return mapData;
		}

		TEST_METHOD(Day12SampleTests)
		{
			MapData map = GetInputFromFile("Data/Day12SampleInput.txt");
			Assert::AreEqual(31u, FewestStepsToBestSignal(map, false));
			Assert::AreEqual(29u, FewestStepsToBestSignal(map, true));
		}

		TEST_METHOD(Day12ActualInputTest)
		{
			MapData map = GetInputFromFile("Data/Day12Input.txt");
			Assert::AreEqual(391u, FewestStepsToBestSignal(map, false));
			Assert::AreEqual(386u, FewestStepsToBestSignal(map, true));
		}
	};
}