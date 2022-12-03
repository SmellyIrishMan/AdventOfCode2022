#include "pch.h"
#include "framework.h"
#include <vector>
#include <unordered_map>

namespace AdventOfCode
{
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