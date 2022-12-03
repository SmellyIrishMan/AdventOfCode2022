#include "pch.h"
#include "framework.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>

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

	//Rock = 0
	//Paper = 1
	//Scissors = 2
	using RockPaperScissorsTurn = std::pair<int, int>;
	using RockPaperScissorsTurnScore = std::pair<int, int>;
	using RockPaperScissorsTurnOutcomes = std::unordered_map<int, std::vector<int>>;
	
	RockPaperScissorsTurnScore RockPaperScissorsScoreRound(RockPaperScissorsTurn turn)
	{
		constexpr unsigned int maxScore = 6;
		static const RockPaperScissorsTurnOutcomes scoreOutcomes = { 
			{0, {3, 0, 6}}, //Rock vs Rock, Paper, Scissors
			{1, {6, 3, 0}}, //Paper vs Rock, Paper, Scissors
			{2, {0, 6, 3}}  //Scissors vs Rock, Paper, Scissors
		};

		const auto scores = scoreOutcomes.find(turn.first);
		if (scores != scoreOutcomes.end())
		{
			unsigned int firstPlayerScore = scores->second[turn.second];
			firstPlayerScore += turn.first + 1;
			unsigned int secondPlayerScore = maxScore - firstPlayerScore + turn.second + 1;
			secondPlayerScore += turn.first + 1;
			return { firstPlayerScore, secondPlayerScore };
		}

		return { 0, 0 };
	}
	
	unsigned int Day2RockPaperScissorsStrategyGuide(std::vector<RockPaperScissorsTurn> Turns)
	{
		unsigned int myScore = 0;
		for (const RockPaperScissorsTurn& turn : Turns)
		{
			RockPaperScissorsTurnScore Score = RockPaperScissorsScoreRound(turn);
			myScore += Score.second;
		}

		return myScore;
	}

	unsigned int Day2RockPaperScissorsStrategyGuideUnlocked(std::vector<RockPaperScissorsTurn> Turns)
	{
		unsigned int myScore = 0;
		for (const RockPaperScissorsTurn& turn : Turns)
		{
			static const RockPaperScissorsTurnOutcomes forcedOutcomes = {
				{0, {2, 0, 1}}, //Rock vs Lose, Draw, Win
				{1, {0, 1, 2}}, //Paper vs Lose, Draw, Win
				{2, {1, 2, 0}}  //Scissors vs Lose, Draw, Win
			};

			const auto forcedOutcome = forcedOutcomes.find(turn.first);
			if (forcedOutcome != forcedOutcomes.end())
			{
				RockPaperScissorsTurnScore Score = RockPaperScissorsScoreRound({ turn.first, forcedOutcome->second[turn.second] });
				myScore += Score.second;
			}
		}

		return myScore;
	}
}