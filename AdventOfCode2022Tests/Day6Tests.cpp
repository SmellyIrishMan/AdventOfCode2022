#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day6.cpp"
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day6Tests)
	{
	public:

		TEST_METHOD(Day6SampleTests)
		{
			std::string example1{ "mjqjpqmgbljsphdztnvjfqwrcgsmlb" };
			std::string example2{ "bvwbjplbgvbhsrlpgdmjqwftvncz" };
			std::string example3{ "nppdvjthqldpwncqszvftbrmjlhg" };
			std::string example4{ "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg" };
			std::string example5{ "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw" };

			Assert::AreEqual(7u, AdventOfCode::Day6::FindMarker(example1, AdventOfCode::Day6::StartOfPacketMarker));
			Assert::AreEqual(5u, AdventOfCode::Day6::FindMarker(example2, AdventOfCode::Day6::StartOfPacketMarker));
			Assert::AreEqual(6u, AdventOfCode::Day6::FindMarker(example3, AdventOfCode::Day6::StartOfPacketMarker));
			Assert::AreEqual(10u, AdventOfCode::Day6::FindMarker(example4, AdventOfCode::Day6::StartOfPacketMarker));
			Assert::AreEqual(11u, AdventOfCode::Day6::FindMarker(example5, AdventOfCode::Day6::StartOfPacketMarker));

			Assert::AreEqual(19u, AdventOfCode::Day6::FindMarker(example1, AdventOfCode::Day6::StartOfMessageMarker));
			Assert::AreEqual(23u, AdventOfCode::Day6::FindMarker(example2, AdventOfCode::Day6::StartOfMessageMarker));
			Assert::AreEqual(23u, AdventOfCode::Day6::FindMarker(example3, AdventOfCode::Day6::StartOfMessageMarker));
			Assert::AreEqual(29u, AdventOfCode::Day6::FindMarker(example4, AdventOfCode::Day6::StartOfMessageMarker));
			Assert::AreEqual(26u, AdventOfCode::Day6::FindMarker(example5, AdventOfCode::Day6::StartOfMessageMarker));
		}

		TEST_METHOD(Day6ActualInputTest)
		{
			unsigned int part1Result;
			unsigned int part2Result;

			std::filesystem::path inputPath{ "Data/Day6Input.txt" };

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				std::string line;
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);
					part1Result = AdventOfCode::Day6::FindMarker(line, AdventOfCode::Day6::StartOfPacketMarker);
					part2Result = AdventOfCode::Day6::FindMarker(line, AdventOfCode::Day6::StartOfMessageMarker);
				}
			}

			Assert::AreEqual(1361u, part1Result);
			Assert::AreEqual(3263u, part2Result);
		}
	};
}