// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "PongGameState.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

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

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> BallMesh;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TObjectPtr<USoundBase> BallHitSFX;
	
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float XMovementSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float YMovementSpeed = 200.0f;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	float XSpeedModifierPerHit = 0.05f;

private:
	float XSpeedMultiplier = 1.0f;
	float YSpeedMultiplier = 0.0f;
};
