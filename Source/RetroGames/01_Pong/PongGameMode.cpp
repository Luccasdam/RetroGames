// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongGameMode.h"
#include "PongGameState.h"


void APongGameMode::StartMatch()
{
	APongGameState* PongGS = GetGameState<APongGameState>();
	if (IsValid(PongGS))
	{
		if (PongGS->GetMatchState() == EMatchState::GameOver)
		{
			PongGS->SetMatchState(EMatchState::Playing);
		}
	}
}

void APongGameMode::RegisterScore(const int32 PlayerIndex)
{
	APongGameState* PongGS = GetGameState<APongGameState>();
	if (IsValid(PongGS))
	{
		if (PongGS->AddPlayerScore(PlayerIndex) == WinningScore)
		{
			PongGS->SetMatchState(EMatchState::GameOver);
		}
	}
}
