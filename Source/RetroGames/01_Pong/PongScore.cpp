// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongScore.h"
#include "PongGameState.h"
#include "Components/TextRenderComponent.h"


APongScore::APongScore()
{
	PrimaryActorTick.bCanEverTick = false;

	ScoreText = CreateDefaultSubobject<UTextRenderComponent>("ScoreText");
	SetRootComponent(ScoreText);
}


void APongScore::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* World = GetWorld();
	if (IsValid(World))
	{
		APongGameState* PongGS = World->GetGameState<APongGameState>();
		if (IsValid(PongGS))
		{
			PongGS->OnPlayerScoreChanged.AddUObject(this, &APongScore::OnPlayerScored);
			PongGS->OnMatchStateChanged.AddDynamic(this, &APongScore::OnMatchStateChanged);
		}
	}

	ScoreText->SetText(FText::AsNumber(0));
}

void APongScore::OnPlayerScored(const int32 ScoringPlayer, const int32 PlayerScore)
{
	if (ScoringPlayer == PlayerIndex)
	{
		ScoreText->SetText(FText::AsNumber(PlayerScore));
	}
}

void APongScore::OnMatchStateChanged(EMatchState NewMatchState)
{
	ScoreText->SetVisibility(NewMatchState != EMatchState::GameOver);
}

