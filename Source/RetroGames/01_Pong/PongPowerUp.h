// This project is made for learning, inspired by Harvard's CS50 Intro to Game Development.

#pragma once

#include "CoreMinimal.h"
#include "PongBall.h"
#include "GameFramework/Actor.h"
#include "PongPowerUp.generated.h"

class UBoxComponent;
class APongPaddle;
class UTextRenderComponent;

class APongPlayerState;


UENUM()
enum class EPowerUpType : uint8
{
	SizeIncrease,
	SpeedIncrease
};


USTRUCT()
struct FPowerUpText
{
	GENERATED_BODY()

	UPROPERTY()
	FText SizeIncreaseText = FText::FromString("Size+");

	UPROPERTY()
	FText SpeedIncreaseText = FText::FromString("Speed+");
};


UCLASS(Abstract)
class RETROGAMES_API APongPowerUp : public AActor
{
	GENERATED_BODY()

	// DECLARE_DYNAMIC_DELEGATE()
	
public:
	APongPowerUp();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnMatchStateChanged(const EMatchState NewMatchState);

	
protected:
	/* Disable PowerUp first then Setup Enable Delay */
	void SetPowerUpDelay();

	/** Enable Power Up - Set Visibility and Collision to true */
	void EnablePowerUp();

	/** Disable Power Up - Set Visibility and Collision to false */
	void DisablePowerUp();


protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UBoxComponent> RootBox;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> PowerUpMesh;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UTextRenderComponent> PowerUpTextRenderComponent;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TObjectPtr<USoundBase> PickUpSFX;

	
	/** Active Power Up */
	UPROPERTY(Transient)
	EPowerUpType PowerUpType;

	/* Text to Display Active Power Up*/
	UPROPERTY(Transient)
	FPowerUpText PowerUpText;

	/* Min/Max Power Up Spawn Time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay")
	FVector2D SpawnInterval = FVector2D(5.f, 10.f);



	/** Max Z Offset from World Center  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay")
	float MaxSpawnZOffset = 200.f;

private:
	FTimerHandle TimerHandle_EnablePowerUp;
};
