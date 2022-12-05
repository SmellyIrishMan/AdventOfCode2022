#include "pch.h"
#include "framework.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

namespace AdventOfCode
{
	using BackpackList = std::vector<std::string>;

	unsigned int ConvertCharToPriority(char c)
	{
		if (c >= 'a' && c <= 'z')
		{
			return (c - 'a') + 1;
		}
		else if (c >= 'A' && c <= 'Z')
		{
			return (c - 'A') + 27;
		}
		return 0;
	}

	unsigned int Day3MisplacedItem(BackpackList backpackList)
	{
		unsigned int commonItemPriorityTotal = 0;
		for (const std::string backpack : backpackList)
		{
			std::unordered_set<char> itemsInFirstComparment(begin(backpack), begin(backpack) + (backpack.size() / 2));
			std::unordered_set<char> itemsInSecondComparment(begin(backpack) + (backpack.size() / 2), end(backpack));

			auto commonItemItr = std::find_first_of(
				begin(itemsInFirstComparment), end(itemsInFirstComparment),
				begin(itemsInSecondComparment), end(itemsInSecondComparment));

			commonItemPriorityTotal += ConvertCharToPriority(*commonItemItr);
		}
		return commonItemPriorityTotal;
	}

	unsigned int Day3TripletBadgeAssignment(BackpackList tripletList)
	{
		std::unordered_set<char> firstBackpackItemSet(tripletList[0].begin(), tripletList[0].end());

		std::unordered_set<char> secondBackpackMatchingItemSet;
		std::for_each(tripletList[1].begin(), tripletList[1].end(), [&](const char& c) {
			if (firstBackpackItemSet.contains(c))
			{
				secondBackpackMatchingItemSet.insert(c);
			}
			});

		std::unordered_set<char> thirdBackpackMatchingItemSet;
		std::for_each(tripletList[2].begin(), tripletList[2].end(), [&](const char& c) {
			if (secondBackpackMatchingItemSet.contains(c))
			{
				thirdBackpackMatchingItemSet.insert(c);
			}
			});

		return ConvertCharToPriority(*thirdBackpackMatchingItemSet.begin());
	}
}