// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongBall.h"

#include "PongPaddle.h"


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

	FHitResult HitResult;
	AddActorWorldOffset(DeltaLocation, true, &HitResult);

	if (HitResult.bBlockingHit)
	{		
		if (HitResult.GetActor()->ActorHasTag(FName("Player")))
		{
			XMovementSpeed = -XMovementSpeed;
		}
		else
		{
			YMovementSpeed = -YMovementSpeed;
		}
	}
}

void APongBall::ResetBall()
{
	SetActorLocation(FVector::ZeroVector);
	XMovementSpeed = -XMovementSpeed;
}

