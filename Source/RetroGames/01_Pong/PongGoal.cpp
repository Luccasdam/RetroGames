// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongGoal.h"
#include "PongBall.h"
#include "PongGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


APongGoal::APongGoal()
{
	PrimaryActorTick.bCanEverTick = false;

	GoalBox = CreateDefaultSubobject<UBoxComponent>("GoalBox");
	SetRootComponent(GoalBox);
}

void APongGoal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GoalBox->OnComponentBeginOverlap.AddDynamic(this, &APongGoal::OnGoalOverlap);
}

void APongGoal::OnGoalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APongBall* PongBall = Cast<APongBall>(OtherActor);
	if (IsValid(PongBall))
	{
		if (IsValid(GoalSFX))
		{
			UGameplayStatics::PlaySound2D(this, GoalSFX);
		}
		
		PongBall->ResetBall();

		const UWorld* World = GetWorld();
		if (IsValid(World))
		{
			APongGameMode* PongGM = World->GetAuthGameMode<APongGameMode>();
			if (IsValid(PongGM))
			{
				PongGM->RegisterScore(ScoringPlayer);
			}
		}
	}
}