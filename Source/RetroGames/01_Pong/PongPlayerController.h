// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

class APongPaddle;


UCLASS()
class RETROGAMES_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TObjectPtr<APongPaddle> P1Paddle;

	UPROPERTY()
	TObjectPtr<APongPaddle> P2Paddle;
	
	void P1MoveUp(float Value);
	void P2MoveUp(float Value);
};
