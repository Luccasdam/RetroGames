// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"


UCLASS()
class RETROGAMES_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartMatch();
	void RegisterScore(const int32 PlayerIndex);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	int32 WinningScore = 5;
};
