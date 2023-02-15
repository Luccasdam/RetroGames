// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongBall.h"
#include "PongPaddle.h"
#include "Kismet/GameplayStatics.h"


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

	if (NewMatchState == EMatchState::Playing)
	{
		YSpeedMultiplier = FMath::RandRange(-1.0f, 1.0f);
	}
}

void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector DeltaLocation = FVector(0.0f, XMovementSpeed * XSpeedMultiplier, YMovementSpeed * YSpeedMultiplier) * DeltaTime;

	FHitResult HitResult;
	AddActorWorldOffset(DeltaLocation, true, &HitResult);

	if (HitResult.bBlockingHit)
	{
		if (IsValid(BallHitSFX))
		{
			UGameplayStatics::PlaySound2D(this, BallHitSFX);
		}
		
		const APongPaddle* PongPaddle = Cast<APongPaddle>(HitResult.GetActor());
		if (IsValid(PongPaddle))
		{
			XMovementSpeed = -XMovementSpeed;
			XSpeedMultiplier += XSpeedModifierPerHit;

			const float HitDistance = GetActorLocation().Z - PongPaddle->GetActorLocation().Z;
			YSpeedMultiplier = HitDistance / PongPaddle->GetPaddleHalfSize();
		}
		else
		{
			YSpeedMultiplier = -YSpeedMultiplier;
		}
	}
}

void APongBall::ResetBall()
{
	SetActorLocation(FVector::ZeroVector);
	XMovementSpeed = -XMovementSpeed;
	XSpeedMultiplier = Cast<APongBall>(APongBall::StaticClass()->GetDefaultObject(true))->GetXSpeedMultiplier();
}

