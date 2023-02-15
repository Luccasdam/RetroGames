// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongBall.h"


APongBall::APongBall()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	SetRootComponent(BallMesh);
}

void APongBall::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* World = GetWorld();
	if (IsValid(World))
	{
		APongGameState* PongGS = World->GetGameState<APongGameState>();
		if (IsValid(PongGS))
		{
			PongGS->OnMatchStateChanged.AddDynamic(this, &APongBall::OnMatchStateChanged);
		}
	}
}

void APongBall::OnMatchStateChanged(const EMatchState NewMatchState)
{
	SetActorTickEnabled(NewMatchState == EMatchState::Playing);
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

