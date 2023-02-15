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
	
	virtual void Tick(float DeltaTime) override;
	
public:
	void SetMovementInput(const float Value) {MovementInput = Value;}
		
	int32 GetPlayerIndex() const {return PlayerIndex;}

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> PaddleMesh;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	float MovementSpeed = 250.0f;

private:
	UPROPERTY(EditInstanceOnly, Category="Gameplay")
	int32 PlayerIndex;
	
	float MovementInput;
};
