// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongGameMode.h"
#include "PongGameState.h"


void APongGameMode::InitGameState()
{
	Super::InitGameState();

	PongGS = GetGameState<APongGameState>();
}

void APongGameMode::StartMatch()
{
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
	if (IsValid(PongGS))
	{
		const int32 NewPlayerScore = PongGS->AddPlayerScore(PlayerIndex);

		FTimerHandle TimerHandle_NextMatchState;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this, &ThisClass::SetNextMatchState, NewPlayerScore);
		GetWorldTimerManager().SetTimer(TimerHandle_NextMatchState, TimerDelegate, BallRespawnDelay, false);	
	}
}

void APongGameMode::SetNextMatchState(const int32 NewPlayerScore)
{
	if (IsValid(PongGS))
	{
		const EMatchState NextMatchState = NewPlayerScore == WinningScore ? EMatchState::GameOver : EMatchState::Waiting;
			
		PongGS->SetMatchState(NextMatchState);
	}
}
