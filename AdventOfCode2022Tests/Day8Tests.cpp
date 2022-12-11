#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day8.cpp"
#include <filesystem>
#include <fstream>
#include <regex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdventOfCode::Day8;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day8Tests)
	{
	public:

		TEST_METHOD(Day8SampleTests)
		{
			ListOfTreeHeightLists input{
				{ 3,0,3,7,3 },
				{ 2,5,5,1,2 },
				{ 6,5,3,3,2 },
				{ 3,3,5,4,9 },
				{ 3,5,3,9,0 } };

			Assert::AreEqual(21u, NumberOfVisibleTrees(input));
			Assert::AreEqual(8u, BestScenicScore(input));
		}

		TEST_METHOD(Day8ActualInputTest)
		{
			ListOfTreeHeightLists input;
			std::filesystem::path inputPath{ "Data/Day8Input.txt" };

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				std::string line;
				constexpr unsigned int zeroCharValue = '0';
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);
					ListOfTreeHeights heights;
					for (char c : line)
					{
						heights.push_back(c - zeroCharValue);
					}
					input.push_back(heights);
				}
			}

			Assert::AreEqual(1'543u, NumberOfVisibleTrees(input));
			Assert::AreEqual(595'080u, BestScenicScore(input));
		}
	};
}