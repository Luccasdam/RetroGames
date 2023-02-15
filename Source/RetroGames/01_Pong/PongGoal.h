// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongGoal.generated.h"

class UBoxComponent;

UCLASS()
class RETROGAMES_API APongGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	APongGoal();
	virtual void PostInitializeComponents() override;

protected:
	UFUNCTION()
	void OnGoalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UBoxComponent> GoalBox;

	UPROPERTY(EditInstanceOnly, Category="Gameplay")
	int32 ScoringPlayer = -1;
};
