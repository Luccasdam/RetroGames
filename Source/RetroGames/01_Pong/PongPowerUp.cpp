// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongPowerUp.h"
#include "PongBall.h"
#include "PongPaddle.h"
#include "PongPlayerState.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APongPowerUp::APongPowerUp()
{
	PrimaryActorTick.bCanEverTick = false;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBox"));
	SetRootComponent(RootBox);
	RootBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUpMesh"));
	PowerUpMesh->SetupAttachment(RootComponent);
	PowerUpMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PowerUpTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PowerUpTextRenderComponent"));
	PowerUpTextRenderComponent->SetupAttachment(PowerUpMesh);
	PowerUpTextRenderComponent->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	PowerUpTextRenderComponent->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
	PowerUpTextRenderComponent->WorldSize = 18.f;
}

// Called when the game starts or when spawned
void APongPowerUp::BeginPlay()
{
	Super::BeginPlay();

	DisablePowerUp();

	if (const UWorld* World = GetWorld())
	{
		if (APongGameState* PongGS = World->GetGameState<APongGameState>())
		{
			PongGS->OnMatchStateChanged.AddDynamic(this, &APongPowerUp::OnMatchStateChanged);
		}
	}
}

// Handle PowerUpState according to MatchState
void APongPowerUp::OnMatchStateChanged(const EMatchState NewMatchState)
{
	if (NewMatchState == EMatchState::Playing)
	{
		DisablePowerUp();
		SetPowerUpDelay();
	}
	else
	{
		DisablePowerUp();
		GetWorldTimerManager().ClearTimer(TimerHandle_EnablePowerUp);
	}
}

// Set Timer to EnablePowerUp
void APongPowerUp::SetPowerUpDelay()
{	
	const float SpawnTime = FMath::RandRange(SpawnInterval.X, SpawnInterval.Y);
	GetWorldTimerManager().SetTimer(TimerHandle_EnablePowerUp, this, &APongPowerUp::EnablePowerUp, SpawnTime);
}

// PowerUp Enabled State
void APongPowerUp::EnablePowerUp()
{
	const float SpawnZOffset = FMath::RandRange(-MaxSpawnZOffset, MaxSpawnZOffset);
	SetActorLocation(FVector::UpVector * SpawnZOffset);
	
	switch (FMath::RandRange(1, 2))
	{
	case 1:
		PowerUpType = EPowerUpType::SizeIncrease;
		PowerUpTextRenderComponent->SetText(PowerUpText.SizeIncreaseText);
		break;
	case 2:
		PowerUpType = EPowerUpType::SpeedIncrease;
		PowerUpTextRenderComponent->SetText(PowerUpText.SpeedIncreaseText);
		break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Enabled PowerUp with invalid PowerUpTypeIndex"))
	}
	
	PowerUpMesh->SetVisibility(true);
	PowerUpTextRenderComponent->SetVisibility(true);
	RootBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// PowerUp Disabled State
void APongPowerUp::DisablePowerUp()
{
	PowerUpMesh->SetVisibility(false);
	PowerUpTextRenderComponent->SetVisibility(false);
	RootBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// PowerUp Activation upon Ball Begin Overlap
void APongPowerUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const APongBall* PongBall = Cast<APongBall>(OtherActor);
	if (!IsValid(PongBall)) return;

	const APongPaddle* InstigatorPaddle = PongBall->GetInstigatorPaddle();
	if (!IsValid(InstigatorPaddle)) return;
	
	APongPlayerState* PongPS = InstigatorPaddle->GetPlayerState<APongPlayerState>();
	if (!IsValid(PongPS)) return;
	
	switch (PowerUpType)
	{
	case EPowerUpType::SizeIncrease:
		PongPS->IncreasePlayerSize(InstigatorPaddle->GetPlayerIndex());
		break;
	case EPowerUpType::SpeedIncrease:
		PongPS->IncreasePlayerSpeed(InstigatorPaddle->GetPlayerIndex());
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Trying to Activate PowerUp with invalid PowerUpType"));
	}

	if (IsValid(PickUpSFX))
	{
		UGameplayStatics::PlaySound2D(this, PickUpSFX);
	}

	DisablePowerUp();
	SetPowerUpDelay();
}
