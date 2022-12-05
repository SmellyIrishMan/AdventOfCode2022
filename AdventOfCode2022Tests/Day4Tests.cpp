#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day4.cpp"
#include <filesystem>
#include <fstream>
#include <regex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day4Tests)
	{
	public:

		TEST_METHOD(Day4SampleTests)
		{
			AdventOfCode::AssignedSectionsPairList sectionPairsList = {
				{{2, 4}, {6, 8}},
				{{2, 3}, {4, 5}},
				{{5, 7}, {7, 9}},
				{{2, 8}, {3, 7}},
				{{6, 6}, {4, 6}},
				{{2, 6}, {4, 8}}
			};
			unsigned int result = AdventOfCode::Day4FindFullyOverlappingSections(sectionPairsList);
			Assert::AreEqual(2u, result);

			unsigned int result2 = AdventOfCode::Day4FindFullOrPartiallyOverlappingSections(sectionPairsList);
			Assert::AreEqual(4u, result2);
		}

		TEST_METHOD(Day4ActualInputTest)
		{
			unsigned int part1Result = 0;
			unsigned int part2Result = 0;

			std::filesystem::path inputPath{ "Data/Day4Input.txt" };

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				AdventOfCode::AssignedSectionsPairList assignedSectionsList;
				std::string line;
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);
					AdventOfCode::AssignedSectionsPair sectionsPair;

					std::smatch matches;
					std::regex regexPattern{ R"((\d*)-(\d*),(\d*)-(\d*))"};
					if (std::regex_search(line, matches, regexPattern))
					{
						AdventOfCode::AssignedSections sectionsA( std::stoul(matches[1].str()), std::stoul(matches[2].str()));
						AdventOfCode::AssignedSections sectionsB(std::stoul(matches[3].str()), std::stoul(matches[4].str()));
						AdventOfCode::AssignedSectionsPair sectionPair(sectionsA, sectionsB);
						assignedSectionsList.push_back(sectionPair);
					}
				}

				part1Result = AdventOfCode::Day4FindFullyOverlappingSections(assignedSectionsList);
				part2Result = AdventOfCode::Day4FindFullOrPartiallyOverlappingSections(assignedSectionsList);
			}

			Assert::AreEqual(485u, part1Result);
			Assert::AreEqual(857u, part2Result);
		}
	};
}
