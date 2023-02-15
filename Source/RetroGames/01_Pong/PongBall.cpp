// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongBall.h"


APongBall::APongBall()
{
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	SetRootComponent(BallMesh);
}

void APongBall::BeginPlay()
{
	Super::BeginPlay();
}

void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector DeltaLocation = FVector(0.0f, XMovementSpeed, YMovementSpeed) * DeltaTime;
	
	AddActorWorldOffset(DeltaLocation);
}

