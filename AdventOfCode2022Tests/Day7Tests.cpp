#include "pch.h"
#include "CppUnitTest.h"
#include "../AdventOfCode2022/Day7.cpp"
#include <filesystem>
#include <fstream>
#include <regex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdventOfCode::Day7;

namespace AdventOfCode2022Tests
{
	TEST_CLASS(Day7Tests)
	{
	public:

		TEST_METHOD(Day7SampleTests)
		{
			std::vector<std::string> terminalOutput{
				{"$ cd /"},
				{ "$ ls" },
				{ "dir a" },
				{ "14848514 b.txt" },
				{ "8504156 c.dat" },
				{ "dir d" },
				{ "$ cd a" },
				{ "$ ls" },
				{ "dir e" },
				{ "29116 f" },
				{ "2557 g" },
				{ "62596 h.lst" },
				{ "$ cd e" },
				{ "$ ls" },
				{ "584 i" },
				{ "$ cd .." },
				{ "$ cd .." },
				{ "$ cd d" },
				{ "$ ls" },
				{ "4060174 j" },
				{ "8033020 d.log" },
				{ "5626152 d.ext" },
				{ "7214296 k" } };

			std::unique_ptr<FilesystemNode> root = BuildFilesystem(terminalOutput);
			Assert::AreEqual(48'381'165u, root->filesize);
			Assert::AreEqual(95'437u, SumLargeDirectories(root.get()));
		}

		TEST_METHOD(Day7ActualInputTest)
		{
			//unsigned int part2Result;

			std::vector<std::string> terminalOutput;
			std::filesystem::path inputPath{ "Data/Day7Input.txt" };

			std::ifstream fileInput{ inputPath };
			if (fileInput)
			{
				std::string line;
				while (!fileInput.eof())
				{
					std::getline(fileInput, line);
					terminalOutput.push_back(line);
				}
			}
			std::unique_ptr<FilesystemNode> root = BuildFilesystem(terminalOutput);

			Assert::AreEqual(1'989'474u, SumLargeDirectories(root.get()));
			Assert::AreEqual(1'111'607u, SizeOfBestFitDirectory(root.get()));
		}
	};
}