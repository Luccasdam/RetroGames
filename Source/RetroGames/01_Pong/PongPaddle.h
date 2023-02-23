// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PongPaddle.generated.h"


UCLASS()
class RETROGAMES_API APongPaddle : public APawn
{
	GENERATED_BODY()

public:
	APongPaddle();

	void NotifyPlayerStateSet();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnMatchStateChanged(const EMatchState NewMatchState);


public:
	virtual void Tick(float DeltaTime) override;
	
public:
	void SetMovementInput(const float Value) {MovementInput = Value;}
		
	int32 GetPlayerIndex() const {return PlayerIndex;}
	float GetPaddleHalfSize() const;

	UFUNCTION()
	void OnPaddleSizeChanged(const int32 PlayerIdx, const int32 NewSizeLevel);

	UFUNCTION()
	void OnPaddleSpeedChanged(const int32 PlayerIdx, const int32 NewSpeedLevel);

	void ResetPaddle();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> PaddleMesh;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	float MovementSpeed = 200.0f;

private:
	UPROPERTY(EditInstanceOnly, Category="Gameplay")
	int32 PlayerIndex;
	
	float MovementInput;

	UPROPERTY(Transient)
	FVector InitialScale;

	UPROPERTY(Transient)
	float InitialSpeed;

protected:
	/** Size Increase Amount for Instigator Paddle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay")
	float SizeIncreaseAmount = 0.1f;

	/** MovementSpeed Increase Amount for Instigator Paddle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay")
	float SpeedIncreaseAmount = 25.f;
};
