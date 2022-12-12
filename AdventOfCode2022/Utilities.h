#pragma once
#include <functional>

namespace AdventOfCode
{
	struct Point2D
	{
		int x;
		int y;
		auto operator<=>(const Point2D&) const = default;
	};
	const auto Point2DComparator = [](Point2D a, Point2D b) { return (a.x < b.y) || (a.x == b.x && a.y < b.y); };

	struct RowColumnLocation
	{
		size_t row;
		size_t col;
	};
	const auto GridLocationComparator = [](RowColumnLocation a, RowColumnLocation b) { return (a.row < b.row) || (a.row == b.row && a.col < b.col); };

	struct Direction2D
	{
		int x;
		int y;
	};
	constexpr Direction2D DirectionNorth{ -1, 0 };
	constexpr Direction2D DirectionSouth{ 1, 0 };
	constexpr Direction2D DirectionEast{ 0, 1 };
	constexpr Direction2D DirectionWest{ 0, -1 };
	constexpr Direction2D DirectionUp{ 0, 1 };
	constexpr Direction2D DirectionDown{ 0, -1 };
	constexpr Direction2D DirectionRight{ 1, 0 };
	constexpr Direction2D DirectionLeft{ -1, 0 };

	enum class Directions
	{
		Up,
		Down,
		Left,
		Right
	};

	float DistanceBetweenTwoPoints(int x1, int y1, int x2, int y2);
}

namespace std
{
	template <>
	struct hash<AdventOfCode::Point2D>
	{
		size_t operator()(AdventOfCode::Point2D const& point) const noexcept
		{
			return ((51 + std::hash<int>()(point.x)) * 51 + std::hash<int>()(point.y));
		}
	};
}