#include "pch.h"
#include "framework.h"
#include <vector>
#include <algorithm>

namespace AdventOfCode
{
	namespace Day11
	{
		using unsigned64 = unsigned long long;

		enum class Operator
		{
			Add,
			Multiply,
			Square
		};

		struct MonkeyData
		{
			std::vector<unsigned64> itemWorryValues;
			Operator operation = Operator::Add;
			unsigned64 operationValue = 0;
			unsigned64 divider = 1;
			std::pair<size_t, size_t> whereToThrow;
			unsigned64 itemsCounted = 0;
		};

		using ListOfMonkeyData = std::vector<MonkeyData>;
		unsigned64 DetermineLevelOfMonkeyBusiness(ListOfMonkeyData monkeyData, unsigned int rounds, bool canReduceWorry)
		{
			for (size_t round = 0; round < rounds; round++)
			{
				for (MonkeyData& data : monkeyData)
				{
					for (unsigned64 itemWorry : data.itemWorryValues)
					{
						switch (data.operation)
						{
						case Operator::Add:
							itemWorry += data.operationValue;
							break;
						case Operator::Multiply:
							itemWorry *= data.operationValue;
							break;
						case Operator::Square:
							itemWorry *= itemWorry;
							break;
						}

						if (canReduceWorry)
						{
							itemWorry /= 3;
						}
						else
						{
							//Do some math to account for the possible +/*/^
							//There are 8 monkeys potentially doing things to the worry level.
						}

						std::vector<unsigned64>& trueTarget = monkeyData[data.whereToThrow.first].itemWorryValues;
						std::vector<unsigned64>& falseTarget = monkeyData[data.whereToThrow.second].itemWorryValues;
						itemWorry % data.divider == 0 ? trueTarget.push_back(itemWorry) : falseTarget.push_back(itemWorry);

						data.itemsCounted++;
					}
					data.itemWorryValues.clear();
				}
			}

			std::vector<unsigned64> sortedCountedTotals;
			for (MonkeyData& data : monkeyData)
			{
				sortedCountedTotals.push_back(data.itemsCounted);
			}
			std::partial_sort(begin(sortedCountedTotals), begin(sortedCountedTotals) + 2, end(sortedCountedTotals), std::greater{});

			return sortedCountedTotals[0] * sortedCountedTotals[1];
		}
	}
}