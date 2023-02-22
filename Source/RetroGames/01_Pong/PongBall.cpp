// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongBall.h"
#include "PongPaddle.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"


APongBall::APongBall()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	SetRootComponent(BallMesh);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>("DirectionArrow");
	DirectionArrow->SetupAttachment(RootComponent);
}

void APongBall::BeginPlay()
{
	Super::BeginPlay();
	
	if (APongGameState* PongGS = GetPongGameState())
	{
		PongGS->OnMatchStateChanged.AddDynamic(this, &APongBall::OnMatchStateChanged);
	}
	
	if (FMath::RandBool()) // If Player 2 Start
	{
		XMovementSpeed = -XMovementSpeed;
		DirectionArrow->SetRelativeRotation(LeftRotation);
	}
}

void APongBall::OnMatchStateChanged(const EMatchState NewMatchState)
{
	SetActorTickEnabled(NewMatchState == EMatchState::Playing);
	DirectionArrow->SetVisibility(NewMatchState == EMatchState::Waiting);

	if (NewMatchState == EMatchState::Waiting)
	{
		if (const APongGameState* PongGS = GetPongGameState())
		{
			const int32 WinningPlayer = PongGS->GetWinningPlayer();
			const FRotator ArrowRotation = WinningPlayer == 0 ? LeftRotation : RightRotation;
			DirectionArrow->SetRelativeRotation(ArrowRotation);
		}
	}

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
		APongPaddle* PongPaddle = Cast<APongPaddle>(HitResult.GetActor());
		if (IsValid(PongPaddle))
		{
			InstigatorPaddle = PongPaddle;
			
			XMovementSpeed = -XMovementSpeed;
			XSpeedMultiplier += XSpeedModifierPerHit;

			const float HitDistance = GetActorLocation().Z - PongPaddle->GetActorLocation().Z;
			YSpeedMultiplier = HitDistance / PongPaddle->GetPaddleHalfSize();

			if (IsValid(BallHitPaddleSFX))
			{
				UGameplayStatics::PlaySound2D(this, BallHitPaddleSFX);
			}
		}
		else
		{
			YSpeedMultiplier = -YSpeedMultiplier;
			
			if (IsValid(BallHitWallSFX))
			{
				UGameplayStatics::PlaySound2D(this, BallHitWallSFX);
			}
		}
	}
}

void APongBall::ResetBall()
{
	SetActorLocation(FVector::ZeroVector);
	XMovementSpeed = -XMovementSpeed;
	XSpeedMultiplier = Cast<APongBall>(APongBall::StaticClass()->GetDefaultObject(true))->GetXSpeedMultiplier();

	InstigatorPaddle = nullptr;
}

APongGameState* APongBall::GetPongGameState() const
{
	const UWorld* World = GetWorld();
	if (IsValid(World))
	{
		APongGameState* PongGS = World->GetGameState<APongGameState>();
		if (IsValid(PongGS))
		{
			return PongGS;
		}
	}

	return nullptr;
}

