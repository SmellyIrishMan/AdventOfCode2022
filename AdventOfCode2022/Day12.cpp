#include "pch.h"
#include "framework.h"
#include "Utilities.h"
#include <vector>
#include <unordered_set>
#include <deque>
#include <iterator>
#include <algorithm>

namespace AdventOfCode
{
	namespace Day12
	{
		struct MapData
		{
			std::vector<std::vector<char>> heightmap;
			RowColumnLocation startingLocation;
			std::vector<RowColumnLocation> potentialStartingLocations;
		};

		struct StepTakenData
		{
			RowColumnLocation location;
			uInt stepsSoFar = 0;

			auto operator<=>(const StepTakenData&) const = default;
		};

		bool IsLocationValid(RowColumnLocation location, const MapData& map, char currentHeight, const std::unordered_set<RowColumnLocation>& exploredLocations)
		{
			const size_t maxRow = map.heightmap.size() - 1;
			const size_t maxCol = map.heightmap[0].size() - 1;
			const bool outOfBounds = location.row < 0 || location.row > maxRow || location.col < 0 || location.col > maxCol;
			if (outOfBounds)
			{
				return false;
			}

			const bool alreadyVisited = exploredLocations.contains(location);
			if (alreadyVisited)
			{
				return false;
			}

			char targetHeight = map.heightmap[location.row][location.col];
			targetHeight == 'E' ? targetHeight = 'z' : targetHeight = targetHeight;
			currentHeight == 'S' ? currentHeight = 'a' : currentHeight = currentHeight;
			const bool tooHigh = (targetHeight - currentHeight) > 1;
			if (tooHigh)
			{
				return false;
			}

			return true;
		}

		uInt FewestStepsToBestSignal(MapData map, bool exploreAllStartingPoints)
		{
			std::vector<RowColumnLocation> startingPositionsToCheck{ map.startingLocation };
			if (exploreAllStartingPoints)
			{
				std::copy(begin(map.potentialStartingLocations), end(map.potentialStartingLocations), std::back_insert_iterator(startingPositionsToCheck));
			}

			std::vector<uInt> startingPositionDistances;
			for (const RowColumnLocation startingPosition : startingPositionsToCheck)
			{
				std::unordered_set<RowColumnLocation> exploredLocations = {};
				std::deque<StepTakenData> locationsToExplore;
				locationsToExplore.push_back({ startingPosition, 0 });

				while (locationsToExplore.size() > 0)
				{
					const StepTakenData traversalData = locationsToExplore.front();
					const RowColumnLocation location = traversalData.location;
					locationsToExplore.pop_front();

					exploredLocations.insert(location);

					const bool foundTarget = map.heightmap[location.row][location.col] == 'E';
					if (foundTarget)
					{
						startingPositionDistances.push_back(traversalData.stepsSoFar);
					}
					else
					{
						std::vector<RowColumnLocation> neighbouringLocations = {
							{ location.row - 1, location.col },
							{ location.row + 1, location.col },
							{ location.row, location.col + 1},
							{ location.row, location.col - 1}
						};
						uInt stepsToThisPoint = traversalData.stepsSoFar + 1;

						for (const RowColumnLocation& neighbouringLocation : neighbouringLocations)
						{
							if (IsLocationValid(neighbouringLocation, map, map.heightmap[location.row][location.col], exploredLocations))
							{
								const auto matchingLocationItr = std::find(begin(locationsToExplore), end(locationsToExplore), traversalData);
								if (matchingLocationItr == end(locationsToExplore))
								{
									locationsToExplore.push_back({ neighbouringLocation, stepsToThisPoint });
								}
							}
						}
					}
				}
			}

			auto smallestPath = std::min_element(begin(startingPositionDistances), end(startingPositionDistances));
			return *smallestPath;
		}
	}
}