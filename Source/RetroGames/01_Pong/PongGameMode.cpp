// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongGameMode.h"
#include "PongGameState.h"


void APongGameMode::RegisterScore(const int32 PlayerIndex)
{
	APongGameState* PongGS = GetGameState<APongGameState>();
	if (IsValid(PongGS))
	{
		if (PongGS->AddPlayerScore(PlayerIndex) == WinningScore)
		{
			GEngine->AddOnScreenDebugMessage(01, 5, FColor::White, FString::Printf(TEXT("Player %i is the Winner!"), PlayerIndex));
		}
	}
}
