#pragma once
#include "pch.h"
#include "framework.h"
#include "Utilities.h"

namespace AdventOfCode
{
	float DistanceBetweenTwoPoints(int x1, int y1, int x2, int y2)
	{
		return static_cast<float>(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0));
	}
}