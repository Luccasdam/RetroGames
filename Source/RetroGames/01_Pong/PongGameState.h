// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"


UCLASS()
class RETROGAMES_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	/* Return the New Player Score Value */
	int32 AddPlayerScore(const int32 PlayerIndex);

private:
	int32 P1Score;
	int32 P2Score;
};
