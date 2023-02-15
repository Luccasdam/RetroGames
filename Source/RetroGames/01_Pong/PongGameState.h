// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"



UENUM()
enum class EMatchState : uint8
{
	Waiting,
	Playing,
	GameOver
};


UCLASS()
class RETROGAMES_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnMatchStateChanged, const EMatchState, NewMatchState);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerScoreChanged, const int32, const int32); // PlayerIndex, PlayerScore
	
public:
	void SetMatchState(const EMatchState NewMatchState);
	EMatchState GetMatchState() const { return MatchState;}
	
	/* Return the New Player Score Value */
	int32 AddPlayerScore(const int32 PlayerIndex);

protected:
	void ResetScores();

	
public:
	UPROPERTY(BlueprintAssignable)
	FOnMatchStateChanged OnMatchStateChanged;
	FOnPlayerScoreChanged OnPlayerScoreChanged;

private:
	EMatchState MatchState = EMatchState::Waiting;
	
	int32 P1Score;
	int32 P2Score;
};
