#include "pch.h"
#include "framework.h"
#include <vector>
#include <set>
#include <string>
#include <algorithm>

namespace AdventOfCode
{
	namespace Day6
	{
		constexpr unsigned int StartOfPacketMarker = 4;
		constexpr unsigned int StartOfMessageMarker = 14;

		unsigned int FindMarker(std::string input, unsigned int uniqueRequirement)
		{
			std::vector<char> mostRecentChars;
			unsigned int distance = 0;
			for (const char& c : input)
			{
				++distance;
				mostRecentChars.push_back(c);
				if (mostRecentChars.size() == uniqueRequirement)
				{
					std::set<char> recentCharSet(begin(mostRecentChars), end(mostRecentChars));
					if (recentCharSet.size() == uniqueRequirement)
					{
						return distance;
					}
					else
					{
						mostRecentChars.erase(begin(mostRecentChars));
					}
				}
			}

			return distance;
		}
	}
}