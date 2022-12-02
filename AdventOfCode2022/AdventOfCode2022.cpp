#include "pch.h"
#include "framework.h"
#include <vector>
#include <numeric>
#include <algorithm>

namespace AdventOfCode
{
	using ElfCalorieLists = std::vector<std::vector<unsigned int>>;
	using ElfCalorieList = std::vector<unsigned int>;

	int64_t Day1HowManyCaloriesPerElf(ElfCalorieLists calorieLists)
	{
		int64_t mostCalories = 0;
		for (const ElfCalorieList& list : calorieLists)
		{
			int64_t listTotal = std::accumulate(list.begin(), list.end(), 0);
			mostCalories = listTotal > mostCalories ? listTotal : mostCalories;
		}

		return mostCalories;
	}

	int64_t Day1HowManyCaloriesAmongTopThreeElfs(ElfCalorieLists calorieLists)
	{
		//TODO Could reduce memory bloat/cycles and track 3 largest as we iterate.
		std::vector<unsigned int> allTotals;
		for (const ElfCalorieList& list : calorieLists)
		{
			allTotals.emplace_back(std::accumulate(list.begin(), list.end(), 0));
		}

		const unsigned int maxElements = static_cast<unsigned int>(std::min(allTotals.size(), static_cast<size_t>(3)));
		std::partial_sort(allTotals.begin(), allTotals.begin() + maxElements, allTotals.end(), std::greater<unsigned int>());

		return std::accumulate(allTotals.begin(), allTotals.begin() + maxElements, 0);;
	}
}