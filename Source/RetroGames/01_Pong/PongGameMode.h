// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

class APongGameState;


UCLASS()
class RETROGAMES_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGameState() override;
	
	void StartMatch();
	void RegisterScore(const int32 PlayerIndex);

private:
	void SetNextMatchState(const int32 NewPlayerScore);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	int32 WinningScore = 5;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float BallRespawnDelay = 1.5f;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APongGameState> PongGS;
};
