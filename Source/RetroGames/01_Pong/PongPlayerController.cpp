// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongPlayerController.h"
#include "PongPaddle.h"
#include "EngineUtils.h"
#include "PongGameMode.h"


void APongPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<APongPaddle> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
	{
		APongPaddle* PongPaddle = *ActorIterator;
		
		if (IsValid(PongPaddle))
		{
			if (PongPaddle->GetPlayerIndex() == 0)
			{
				P1Paddle = PongPaddle;
			}
			else if (PongPaddle->GetPlayerIndex() == 1)
			{
				P2Paddle = PongPaddle;
			}
		}
	}
}


void APongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("P1MoveUp", this, &APongPlayerController::P1MoveUp);
	InputComponent->BindAxis("P2MoveUp", this, &APongPlayerController::P2MoveUp);

	InputComponent->BindAction("Start", IE_Pressed, this, &APongPlayerController::StartPressed);
}

void APongPlayerController::P1MoveUp(float Value)
{
	if (IsValid(P1Paddle))
	{
		P1Paddle->SetMovementInput(Value);
	}
}

void APongPlayerController::P2MoveUp(float Value)
{
	if (IsValid(P2Paddle))
	{
		P2Paddle->SetMovementInput(Value);
	}
}

void APongPlayerController::StartPressed()
{
	const UWorld* World = GetWorld();
	if (IsValid(World))
	{
		APongGameMode* PongGM = World->GetAuthGameMode<APongGameMode>();
		if (IsValid(PongGM))
		{
			PongGM->StartMatch();
		}
	}
}
