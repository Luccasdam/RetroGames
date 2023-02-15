// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongGameState.h"

int32 APongGameState::AddPlayerScore(const int32 PlayerIndex)
{
	const int32 NewScore = PlayerIndex == 0 ? ++P1Score : ++P2Score;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::Printf(TEXT("Player %i NewScore: %i"), PlayerIndex, NewScore));
	return NewScore;
}
