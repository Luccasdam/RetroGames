// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "PongGameState.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

class UArrowComponent;
class APongPaddle;

UCLASS()
class RETROGAMES_API APongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	APongBall();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnMatchStateChanged(const EMatchState NewMatchState);

public:	
	virtual void Tick(float DeltaTime) override;

	void ResetBall();

	float GetXSpeedMultiplier() const {return XSpeedMultiplier;}
	APongGameState* GetPongGameState() const;

	APongPaddle* GetInstigatorPaddle() const {return InstigatorPaddle.Get();}

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> BallMesh;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UArrowComponent> DirectionArrow;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TObjectPtr<USoundBase> BallHitPaddleSFX;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TObjectPtr<USoundBase> BallHitWallSFX;
	
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float XMovementSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float YMovementSpeed = 200.0f;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	float XSpeedModifierPerHit = 0.75f;

private:
	float XSpeedMultiplier = 1.0f;
	float YSpeedMultiplier = 0.0f;

	FRotator LeftRotation = FRotator(0.0f, -90.0f, 0.0f);
	FRotator RightRotation = FRotator(0.0f, 90.0f, 0.0f);

	UPROPERTY(Transient)
	TWeakObjectPtr<APongPaddle> InstigatorPaddle;
};
