// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongGoal.h"

// Sets default values
APongGoal::APongGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APongGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APongGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

