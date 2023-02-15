// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongPaddle.h"

#define METERS_TO_CENTIMETERS 100.0f


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

float APongPaddle::GetPaddleHalfSize() const
{
	return PaddleMesh->GetComponentScale().Z * METERS_TO_CENTIMETERS * 0.5f;
}
