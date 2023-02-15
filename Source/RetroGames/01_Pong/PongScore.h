// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "PongGameState.h"
#include "GameFramework/Actor.h"
#include "PongScore.generated.h"

class UTextRenderComponent;

UCLASS()
class RETROGAMES_API APongScore : public AActor
{
	GENERATED_BODY()
	
public:	
	APongScore();

protected:
	virtual void BeginPlay() override;
	
	void OnPlayerScored(const int32 ScoringPlayer, const int32 PlayerScore);

	UFUNCTION()
	void OnMatchStateChanged(EMatchState NewMatchState);

	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UTextRenderComponent> ScoreText;
	
	UPROPERTY(EditInstanceOnly, Category="Gameplay")
	int32 PlayerIndex = -1;
};
