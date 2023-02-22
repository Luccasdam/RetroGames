// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.


#include "PongPlayerState.h"

#include "PongGameState.h"

void APongPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* World = GetWorld())
	{
		if (APongGameState* PongGS = World->GetGameState<APongGameState>())
		{
			PongGS->OnMatchStateChanged.AddDynamic(this, &APongPlayerState::OnMatchStateChanged);
		}
	}
}

void APongPlayerState::OnMatchStateChanged(const EMatchState NewMatchState)
{
	if (NewMatchState == EMatchState::GameOver)
	{
		ResetPlayerState();
	}
}

void APongPlayerState::IncreasePlayerSize(const int32 PlayerIdx)
{
	const int32 NewExtraSize = PlayerIdx == 0 ? ++P1ExtraSize : ++P2ExtraSize;
	OnPlayerSizeChanged.Broadcast(PlayerIdx, NewExtraSize);
}

void APongPlayerState::IncreasePlayerSpeed(const int32 PlayerIdx)
{
	const int32 NewExtraSpeed = PlayerIdx == 0 ? ++P1ExtraSpeed : ++P2ExtraSpeed;
	OnPlayerSpeedChanged.Broadcast(PlayerIdx, NewExtraSpeed);
}


void APongPlayerState::ResetPlayerState()
{
	P1ExtraSize = 0;
	P1ExtraSpeed = 0;
	P2ExtraSize = 0;
	P2ExtraSpeed = 0;

	OnPlayerSizeChanged.Broadcast(0, P1ExtraSize);
	OnPlayerSpeedChanged.Broadcast(0, P1ExtraSpeed);

	OnPlayerSizeChanged.Broadcast(1, P2ExtraSize);
	OnPlayerSizeChanged.Broadcast(1, P2ExtraSpeed);
}