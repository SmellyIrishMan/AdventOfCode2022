#include "pch.h"
#include "framework.h"
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "Utilities.h"

namespace AdventOfCode
{
	namespace Day9
	{
		struct Move
		{
			AdventOfCode::Direction2D direction;
			unsigned int steps;
		};
		using ListOfMoves = std::vector<Move>;

		unsigned int CountUniqueTailPositions(ListOfMoves moves, unsigned int ropeLength)
		{
			std::vector<Point2D> rope(ropeLength);
			std::fill(begin(rope), end(rope), Point2D{ 0, 0 });

			std::unordered_set<Point2D> tailUniquePoints;
			tailUniquePoints.insert(rope.back());

			for (const Move& move : moves)
			{
				unsigned int stepsRemaining = move.steps;
				while (stepsRemaining > 0)
				{
					rope[0].x += move.direction.x;
					rope[0].y += move.direction.y;

					for (size_t ropeIndex = 0; ropeIndex < ropeLength - 1; ropeIndex++)
					{
						size_t nextIndex = ropeIndex + 1;
						float distance = DistanceBetweenTwoPoints(rope[ropeIndex].x, rope[ropeIndex].y, rope[nextIndex].x, rope[nextIndex].y);
						float nextPointTooFarDistance = 1.9f;
						if (distance > nextPointTooFarDistance)
						{
							Direction2D direction = { rope[ropeIndex].x - rope[nextIndex].x, rope[ropeIndex].y - rope[nextIndex].y };
							direction.x = std::clamp(direction.x, -1, 1);
							direction.y = std::clamp(direction.y, -1, 1);
							rope[nextIndex].x += direction.x;
							rope[nextIndex].y += direction.y;
						}
					}
					tailUniquePoints.insert(rope.back());

					stepsRemaining--;
				}
			}

			return static_cast<unsigned int>(tailUniquePoints.size());
		}
	}
}