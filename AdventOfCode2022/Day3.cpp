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
			std::string firstCompartment = backpack.substr(0, backpack.size() / 2);
			std::unordered_set<char> itemsInFirstComparment;
			for (const char c : firstCompartment)
			{
				itemsInFirstComparment.insert(c);
			}

			std::string secondComparment = backpack.substr(backpack.size() / 2);
			char commonItem = '-';
			for (const char c : secondComparment)
			{
				if (itemsInFirstComparment.contains(c))
				{
					commonItem = c;
					break;
				}
			}
			commonItemPriorityTotal += ConvertCharToPriority(commonItem);
		}
		return commonItemPriorityTotal;
	}

	unsigned int Day3TripletBadgeAssignment(BackpackList tripletList)
	{
		std::unordered_set<char> matchingItemsInCurrentBackpack;
		std::for_each(tripletList[0].begin(), tripletList[0].end(), [&](const char& c) {
			matchingItemsInCurrentBackpack.insert(c);
		});
		
		bool first = true;
		std::unordered_set<char> itemsInPreviousBackpack;;
		for (const std::string& backpack : tripletList)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				itemsInPreviousBackpack = std::move(matchingItemsInCurrentBackpack);
				matchingItemsInCurrentBackpack.clear();

				for (const char c : backpack)
				{
					if (itemsInPreviousBackpack.contains(c))
					{
						matchingItemsInCurrentBackpack.insert(c);
					}
				}
			}
		}

		return ConvertCharToPriority(*matchingItemsInCurrentBackpack.begin());
	}
}