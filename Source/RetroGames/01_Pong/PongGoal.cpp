// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongGoal.h"
#include "PongBall.h"
#include "Components/BoxComponent.h"


APongGoal::APongGoal()
{
	PrimaryActorTick.bCanEverTick = true;

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
		PongBall->ResetBall();
	}
}