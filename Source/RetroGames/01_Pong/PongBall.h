// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
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

public:	
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> BallMesh;

private:
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float XMovementSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float YMovementSpeed = 200.0f;
};
