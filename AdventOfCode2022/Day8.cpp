#include "pch.h"
#include "framework.h"
#include <vector>
#include <set>

namespace AdventOfCode
{
	namespace Day8
	{
		using ListOfTreeHeights = std::vector<unsigned int>;
		using ListOfTreeHeightLists = std::vector<std::vector<unsigned int>>;

		struct GridLocation
		{
			size_t row;
			size_t col;
		};
		auto GridLocationComparator = [](GridLocation a, GridLocation b) { return (a.row < b.row) || (a.row == b.row && a.col < b.col); };

		struct Direction
		{
			int x;
			int y;
		};

		using LocationSet = std::set<GridLocation, decltype(GridLocationComparator)>;

		enum class HeightTestResult
		{
			Visible,
			NotVisible,
			Uncertain
		};

		HeightTestResult HeightIsVisible(unsigned int height, unsigned int neighbourHeightMin, unsigned int distantHeightMin)
		{
			if (height > neighbourHeightMin)
			{
				return HeightTestResult::Visible;
			}
			else if (height <= neighbourHeightMin && height <= distantHeightMin)
			{
				return HeightTestResult::NotVisible;
			}

			return HeightTestResult::Uncertain;
		}

		std::vector<size_t> ProcessLine(ListOfTreeHeights heightList, unsigned int nearHeightMin, unsigned int farHeightMin)
		{
			std::vector<size_t> visibleIndices;
			size_t nearIndex = 0;
			size_t farIndex = heightList.size() - 1;
			while (nearIndex <= farIndex)
			{
				switch (HeightIsVisible(heightList[nearIndex], nearHeightMin, farHeightMin))
				{
				case HeightTestResult::Visible:
					nearHeightMin = heightList[nearIndex];
					visibleIndices.push_back(nearIndex);
					nearIndex += 1;
					break;
				case HeightTestResult::NotVisible:
					nearIndex += 1;
					break;
				case HeightTestResult::Uncertain:
					break;
				}

				if (nearIndex > farIndex)
				{
					break;
				}

				switch (HeightIsVisible(heightList[farIndex], farHeightMin, nearHeightMin))
				{
				case HeightTestResult::Visible:
					farHeightMin = heightList[farIndex];
					visibleIndices.push_back(farIndex);
					farIndex > 0 ? farIndex -= 1 : 0;
					break;
				case HeightTestResult::NotVisible:
					farIndex > 0 ? farIndex -= 1 : 0;
					break;
				case HeightTestResult::Uncertain:
					break;
				}
			}

			return visibleIndices;
		}

		ListOfTreeHeights CreateList(const ListOfTreeHeightLists& grid, GridLocation start, Direction direction, size_t num)
		{
			ListOfTreeHeights treeLine;
			GridLocation currentLocation = start;

			const size_t gridWidth = grid[0].size();
			const size_t gridHeight = grid.size();

			while (treeLine.size() < num)
			{
				treeLine.push_back(grid[currentLocation.row][currentLocation.col]);
				currentLocation.row += direction.x;
				currentLocation.col += direction.y;
			}

			return treeLine;
		}


		unsigned int NumberOfVisibleTrees(ListOfTreeHeightLists treeHeightLists)
		{
			LocationSet visibleTreeLocations;
			
			const size_t gridWidth = treeHeightLists[0].size();
			const size_t gridHeight = treeHeightLists.size();
			const size_t outsideElementCount = (gridWidth * 2) + ((gridHeight - 2) * 2);

			//Rows
			for (size_t row = 1; row < gridHeight - 1; ++row)
			{
				ListOfTreeHeights line = CreateList(treeHeightLists, { row, 1 }, { 0, 1 }, gridWidth - 2 );
				std::vector<size_t> visibleIndexes = ProcessLine(line, treeHeightLists[row][0], treeHeightLists[row][gridWidth - 1]);
				for (size_t index : visibleIndexes)
				{
					visibleTreeLocations.insert({ row, index + 1 });
				}
			}

			//Columns
			for (size_t column = 1; column < gridWidth - 1; ++column)
			{
				ListOfTreeHeights line = CreateList(treeHeightLists, { 1, column }, { 1, 0 }, gridHeight - 2 );
				std::vector<size_t> visibleIndexes = ProcessLine(line, treeHeightLists[0][column], treeHeightLists[gridHeight - 1][column]);
				for (size_t index : visibleIndexes)
				{
					visibleTreeLocations.insert({ index + 1, column });
				}
			}

			return static_cast<unsigned int>(visibleTreeLocations.size() + outsideElementCount);
		}

		unsigned int GetScenicScoreForLine(ListOfTreeHeights heights)
		{
			if (heights.size() <= 1)
			{
				return 0;
			}

			unsigned int baseHeight = heights[0];
			unsigned int score = 0;
			for (size_t i = 1; i < heights.size(); i++)
			{
				if (heights[i] >= baseHeight)
				{
					score++;
					return score;
				}
				else
				{
					score++;
				}
			}

			return score;
		}

		unsigned int BestScenicScore(ListOfTreeHeightLists treeHeightLists)
		{
			unsigned int bestScore = 0;

			const size_t gridWidth = treeHeightLists[0].size();
			const size_t gridHeight = treeHeightLists.size();

			for (size_t row = 0; row < gridHeight - 1; ++row)
			{
				for (size_t col = 0; col < gridWidth - 1; ++col)
				{
					ListOfTreeHeights North = CreateList(treeHeightLists, {row, col}, { -1, 0}, row + 1);
					ListOfTreeHeights South = CreateList(treeHeightLists, {row, col}, { 1, 0 }, gridHeight - row);
					ListOfTreeHeights East = CreateList(treeHeightLists, {row, col}, { 0, 1 }, gridWidth - col);
					ListOfTreeHeights West = CreateList(treeHeightLists, {row, col}, { 0, -1 }, col + 1);

					unsigned int northScore = GetScenicScoreForLine(North);
					unsigned int southScore = GetScenicScoreForLine(South);
					unsigned int eastScore = GetScenicScoreForLine(East);
					unsigned int westScore = GetScenicScoreForLine(West);

					unsigned int score = northScore * southScore * eastScore * westScore;
					if (score > bestScore)
					{
						bestScore = score;
					}
				}
			}

			return bestScore;
		}
	}
}