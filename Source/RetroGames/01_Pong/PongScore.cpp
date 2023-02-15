// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongScore.h"

// Sets default values
APongScore::APongScore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APongScore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APongScore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

