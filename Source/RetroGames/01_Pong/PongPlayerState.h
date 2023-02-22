// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "PongGameState.h"
#include "GameFramework/PlayerState.h"
#include "PongPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RETROGAMES_API APongPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSizeChanged, int32, PlayerIdx, int32, ExtraSize);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSpeedChanged, int32, PlayerIdx, int32, ExtraSpeed);

public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerSizeChanged OnPlayerSizeChanged;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerSpeedChanged OnPlayerSpeedChanged;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnMatchStateChanged(const EMatchState NewMatchState);

public:
	void IncreasePlayerSize(int32 PlayerIdx);
	void IncreasePlayerSpeed(int32 PlayerIdx);

	void ResetPlayerState();

protected:
	UPROPERTY(Transient)
	int32 P1ExtraSize = 0;

	UPROPERTY(Transient)
	int32 P1ExtraSpeed = 0;

	UPROPERTY(Transient)
	int32 P2ExtraSize = 0;

	UPROPERTY(Transient)
	int32 P2ExtraSpeed = 0;
};
