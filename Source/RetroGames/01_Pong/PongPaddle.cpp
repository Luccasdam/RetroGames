// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongPaddle.h"


APongPaddle::APongPaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>("PaddleMesh");
	SetRootComponent(PaddleMesh);
}


void APongPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float DeltaMovement = MovementInput * MovementSpeed * DeltaTime;
	const FVector DeltaLocation = FVector::UpVector * DeltaMovement;
	AddActorWorldOffset(DeltaLocation, true);
}