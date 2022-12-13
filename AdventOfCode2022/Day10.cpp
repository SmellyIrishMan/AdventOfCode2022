#include "pch.h"
#include "framework.h"
#include <array>
#include <queue>
#include <vector>
#include <numeric>

namespace AdventOfCode
{
	namespace Day10
	{
		enum class InstructionType
		{
			NoOp,
			AddX
		};

		struct Instruction
		{
			InstructionType type = InstructionType::NoOp;
			int data = 0;
		};

		using ListOfInstructions = std::vector<Instruction>;
		int CombineSignalStrength(ListOfInstructions instructions)
		{			
			std::vector<int> registerAdjustments{ };
			for (const Instruction& instruction : instructions)
			{
				switch (instruction.type)
				{
				case InstructionType::NoOp:
					registerAdjustments.push_back(0);
					break;
				case InstructionType::AddX:
					registerAdjustments.push_back(0);
					registerAdjustments.push_back(instruction.data);
					break;
				}
			}

			int combinedSignalStrength = 0;
			int xRegister = 1;
			std::array<char, 240> screenOutput({ '-' });
			std::queue<unsigned int> cycleCheckpoints({ 20, 60, 100, 140, 180, 220 });
			int cycle = 1;
			for (int adjustment : registerAdjustments)
			{
				if (!cycleCheckpoints.empty() && cycle == cycleCheckpoints.front())
				{
					combinedSignalStrength += xRegister * cycleCheckpoints.front();
					cycleCheckpoints.pop();
				}

				int pixelIndex = (cycle - 1) % 40;
				screenOutput[cycle - 1] = abs(pixelIndex - xRegister) <= 1 ? '#' : '.';
				xRegister += adjustment;
				cycle++;
			}

			return combinedSignalStrength;
		}
	}
}