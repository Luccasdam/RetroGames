// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongGameMode.h"
#include "PongGameState.h"


void APongGameMode::StartMatch()
{
	APongGameState* PongGS = GetGameState<APongGameState>();
	if (IsValid(PongGS))
	{
		switch (PongGS->GetMatchState())
		{
		case EMatchState::Waiting:
			PongGS->SetMatchState(EMatchState::Playing);
			break;
		case EMatchState::Playing:
			break;
		case EMatchState::GameOver:
			PongGS->SetMatchState(EMatchState::Waiting);
			break;
		}
	}
}

void APongGameMode::RegisterScore(const int32 PlayerIndex)
{
	APongGameState* PongGS = GetGameState<APongGameState>();
	if (IsValid(PongGS))
	{
		const int32 NewPlayerScore = PongGS->AddPlayerScore(PlayerIndex);
		const EMatchState NextMatchState = NewPlayerScore == WinningScore ? EMatchState::GameOver : EMatchState::Waiting;
		
		PongGS->SetMatchState(NextMatchState);
	}
}
