#include "pch.h"
#include "framework.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

namespace AdventOfCode
{
	namespace Day5 
	{
		using Stacks = std::vector<std::vector<char>>;
		using StackMove = std::tuple<unsigned int, unsigned int, unsigned int>;
		using StackMoves = std::vector<StackMove>;

		enum class CraneOrdering
		{
			KeepOrder,
			ReverseOrder
		};
	}

	namespace 
	{
		void MoveElements(Day5::Stacks& stacks, unsigned int numElements, unsigned int fromStack, unsigned int toStack, Day5::CraneOrdering ordering)
		{
			const auto& firstItr = begin(stacks[fromStack]) + (stacks[fromStack].size() - numElements);
			switch (ordering)
			{
			case Day5::CraneOrdering::KeepOrder:
				std::copy(firstItr, end(stacks[fromStack]), std::back_inserter(stacks[toStack]));
				break;
			case Day5::CraneOrdering::ReverseOrder:
				std::reverse_copy(firstItr, end(stacks[fromStack]), std::back_inserter(stacks[toStack]));
				break;
			}

			stacks[fromStack].erase(end(stacks[fromStack]) - numElements, end(stacks[fromStack]));
		}
	}

	std::string Day5ArrangeStacks(Day5::Stacks stacks, Day5::StackMoves moves, Day5::CraneOrdering ordering)
	{
		for (const Day5::StackMove move : moves)
		{
			const auto [count, from, to] = move;
			MoveElements(stacks, count, from, to, ordering);
		}

		std::string result;
		std::for_each(begin(stacks), end(stacks), [&](const std::vector<char>& stack)
		{
			result.push_back(stack.back());
		});

		return result;
	}

	//I think I could have a vector of all the elements and just move things around within that right?
	//And then have a stack index.

	//Otherwise just have a vector of vectors, and remove/append to those.
	//It's not very fancy but it is effective.
}