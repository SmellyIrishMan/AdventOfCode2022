#include "pch.h"
#include "framework.h"
#include <vector>
#include <regex>
#include <string>
#include <memory>
#include <cassert>
#include <algorithm>

namespace AdventOfCode
{
	namespace Day7
	{
		struct FilesystemNode
		{
			std::string name;
			unsigned int filesize = 0;

			FilesystemNode* Parent = nullptr;
			std::vector<std::unique_ptr<FilesystemNode>> ChildNodes;

			bool IsRoot() { return Parent == nullptr; }
			bool IsFile() { return ChildNodes.size() == 0; }
			bool IsDirectory() { return ChildNodes.size() > 0; }
		};

		void CalculateDirectorySizes(FilesystemNode* root)
		{
			unsigned int size = 0;
			for (std::unique_ptr<FilesystemNode>& node : root->ChildNodes)
			{
				if (node->IsFile())
				{
					size += node->filesize;
				}
				else
				{
					CalculateDirectorySizes(node.get());
					size += node->filesize;
				}
			}

			root->filesize = size;
		}

		//TODO Could have just build a map instead?
		//	Would need to protect against file/directory conflicts
		//	Always append the key to the value to search for the matching item?
		//["/"]=>["a", "b.txt", "c.dat", "d"]
		//["/a"]=>["/e", "f", "g", "h.lst"]
		//["/a/e"]=>["i"]
		//["/a/e/i"]=>[]
		//["/d"]=>["j", "d.log", "d.ext", "k"]
		//["/b.txt"]=>14848514
		//["/c.dat"]=>8504156

		std::unique_ptr<FilesystemNode> BuildFilesystem(std::vector<std::string> terminalOutput)
		{
			std::unique_ptr<FilesystemNode> root = std::make_unique<FilesystemNode>();
			FilesystemNode* currentDirectory = root.get();

			std::regex commandMatchingPattern{ R"(\$ ((cd (\w+|/|..)|ls)))" };
			std::regex directoryPattern{ R"(dir (\w+))" };
			std::regex filePattern{ R"((\d+) (.*))" };
			std::smatch matches;
			for (const auto& line : terminalOutput)
			{
				if (std::regex_search(line, matches, commandMatchingPattern))
				{
					if (matches[1].str() == "ls")
					{
						continue;
					}
					else
					{
						const std::string dirName = matches[3].str();
						if (dirName == "/")
						{
							currentDirectory = root.get();
						}
						else if (dirName == "..")
						{
							currentDirectory = currentDirectory->Parent;
						}
						else
						{
							const auto& directoryItr = std::find_if(begin(currentDirectory->ChildNodes), end(currentDirectory->ChildNodes), [&](const std::unique_ptr<FilesystemNode>& node) {
								return node->name == dirName;
								});

							currentDirectory = (*directoryItr).get();
						}
					}
				}
				else if (std::regex_search(line, matches, directoryPattern))
				{
					const std::string dirName = matches[1].str();
					const auto& directoryItr = std::find_if(begin(currentDirectory->ChildNodes), end(currentDirectory->ChildNodes), [&](const std::unique_ptr<FilesystemNode>& node) {
						return node->name == dirName;
						});

					if (directoryItr == end(currentDirectory->ChildNodes))
					{
						std::unique_ptr<FilesystemNode> newDirectory = std::make_unique<FilesystemNode>();
						newDirectory->name = dirName;
						newDirectory->Parent = currentDirectory;
						currentDirectory->ChildNodes.emplace_back(std::move(newDirectory));
					}
				}
				else if (std::regex_search(line, matches, filePattern))
				{
					const unsigned int fileSize = std::stoul(matches[1].str());
					const std::string fileName = matches[2].str();
					const auto& directoryItr = std::find_if(begin(currentDirectory->ChildNodes), end(currentDirectory->ChildNodes), [&](const std::unique_ptr<FilesystemNode>& node) {
						return node->name == fileName;
						});
					if (directoryItr == end(currentDirectory->ChildNodes))
					{
						std::unique_ptr<FilesystemNode> newFile = std::make_unique<FilesystemNode>();
						newFile->name = fileName;
						newFile->filesize = fileSize;
						newFile->Parent = currentDirectory;
						currentDirectory->ChildNodes.emplace_back(std::move(newFile));
					}
				}
				else
				{
					assert(false);	//We should be reading either a valid command or file.
				}
			}

			CalculateDirectorySizes(root.get());

			return std::move(root);
		}

		unsigned int SumLargeDirectories(FilesystemNode* root)
		{
			constexpr unsigned int maxDirectorySize = 100'000;

			unsigned int size = 0;
			for (const std::unique_ptr<FilesystemNode>& node : root->ChildNodes)
			{
				if (node->IsDirectory())
				{
					if (node->filesize <= maxDirectorySize)
					{
						size += node->filesize;
					}
					size += SumLargeDirectories(node.get());
				}
			}

			return size;
		}

		constexpr unsigned int maxDirectorySize = 70000000;
		constexpr unsigned int spaceRequired = 30000000;

		unsigned int FindBestFitDirectory(FilesystemNode* node, unsigned int minSizeRequired, unsigned int& currentBestFit)
		{
			unsigned int size = 0;
			for (const std::unique_ptr<FilesystemNode>& node : node->ChildNodes)
			{
				if (node->IsDirectory())
				{
					if (node->filesize >= minSizeRequired && node->filesize < currentBestFit)
					{
						currentBestFit = node->filesize;
					}
					currentBestFit = FindBestFitDirectory(node.get(), minSizeRequired, currentBestFit);
				}
			}

			return currentBestFit;
		}

		unsigned int SizeOfBestFitDirectory(FilesystemNode* root)
		{
			unsigned int currentSpaceRemaining = maxDirectorySize - root->filesize;
			unsigned int minSizeRequired = spaceRequired - currentSpaceRemaining;
			unsigned int sizeOfBestDirectory = FindBestFitDirectory(root, minSizeRequired, root->filesize);

			return sizeOfBestDirectory;
		}
	}
}