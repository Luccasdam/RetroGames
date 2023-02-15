// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongScore.generated.h"

UCLASS()
class RETROGAMES_API APongScore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APongScore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
