// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongPaddle.h"

// Sets default values
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

void APongPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent)

	PlayerInputComponent->BindAxis("P1MoveUp", this, &APongPaddle::SetMovementInput);
}

