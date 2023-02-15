// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongGameState.h"

void APongGameState::SetMatchState(const EMatchState NewMatchState)
{
	MatchState = NewMatchState;
	OnMatchStateChanged.Broadcast(MatchState);

	if (MatchState == EMatchState::GameOver)
	{
		ResetScores();
	}
}

int32 APongGameState::AddPlayerScore(const int32 PlayerIndex)
{
	const int32 NewScore = PlayerIndex == 0 ? ++P1Score : ++P2Score;
	OnPlayerScoreChanged.Broadcast(PlayerIndex, NewScore);

	WinningPlayer = P1Score > P2Score ? 0 : 1;
	
	return NewScore;
}

void APongGameState::ResetScores()
{
	P1Score = 0;
	P2Score = 0;
	OnPlayerScoreChanged.Broadcast(0, P1Score);
	OnPlayerScoreChanged.Broadcast(1, P2Score);
}
