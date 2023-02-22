// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongPaddle.h"
#include "PongGameState.h"
#include "PongPlayerState.h"

#define METERS_TO_CENTIMETERS 100.0f


APongPaddle::APongPaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>("PaddleMesh");
	SetRootComponent(PaddleMesh);
}

void APongPaddle::NotifyPlayerStateSet()
{
	if (APongPlayerState* PongPS = GetPlayerState<APongPlayerState>())
	{
		PongPS->OnPlayerSizeChanged.AddDynamic(this, &APongPaddle::OnPaddleSizeChanged);
		PongPS->OnPlayerSpeedChanged.AddDynamic(this, &APongPaddle::OnPaddleSpeedChanged);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Paddle failed to access PongPS"));
	}
}

void APongPaddle::BeginPlay()
{
	Super::BeginPlay();

	InitialScale = GetActorScale3D();
	InitialSpeed = MovementSpeed;

	if (const UWorld* World = GetWorld())
	{
		if (APongGameState* PongGS = World->GetGameState<APongGameState>())
		{
			PongGS->OnMatchStateChanged.AddDynamic(this, &APongPaddle::OnMatchStateChanged);
		}
	}
}

void APongPaddle::OnMatchStateChanged(const EMatchState NewMatchState)
{
	if (NewMatchState == EMatchState::GameOver)
	{
		ResetPaddle();
	}
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


void APongPaddle::OnPaddleSizeChanged(const int32 PlayerIdx, const int32 NewSizeLevel)
{
	if (PlayerIdx == PlayerIndex)
	{
		const FVector DeltaScale = FVector::UpVector * SizeIncreaseAmount * NewSizeLevel;
		PaddleMesh->SetWorldScale3D(InitialScale + DeltaScale);
	}
}

void APongPaddle::OnPaddleSpeedChanged(const int32 PlayerIdx, const int32 NewSpeedLevel)
{
	if (PlayerIdx == PlayerIndex)
	{
		MovementSpeed = InitialSpeed + SpeedIncreaseAmount * NewSpeedLevel;
	}
}

void APongPaddle::ResetPaddle()
{
	MovementSpeed = InitialSpeed;
	PaddleMesh->SetWorldScale3D(InitialScale);
}