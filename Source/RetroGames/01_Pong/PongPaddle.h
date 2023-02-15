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
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SetMovementInput(float Value) {MovementInput = Value;}

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> PaddleMesh;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	float MovementSpeed = 250.0f;

private:
	float MovementInput;
};
