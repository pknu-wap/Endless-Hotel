// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include <CoreMinimal.h>
#include <LobbyDoor.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ALobbyDoor : public AInteractBase
{
	GENERATED_BODY()

#pragma region Base

public:
	ALobbyDoor(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Door

private:
	void RotateDoor(FRotator LeftRot, FRotator RightRot, USoundWave* DoorSound, float Duration);

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> DoorLeft;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> DoorRight;

	FRotator LeftCloseRot;
	FRotator RightCloseRot;

	UPROPERTY(EditDefaultsOnly, Category = "Door")
	FRotator LeftOpenRot;

	UPROPERTY(EditDefaultsOnly, Category = "Door")
	FRotator RightOpenRot;

	UPROPERTY(EditDefaultsOnly, Category = "Door")
	TObjectPtr<USoundWave> SW_DoorOpen;

	UPROPERTY(EditDefaultsOnly, Category = "Door")
	TObjectPtr<USoundWave> SW_DoorClose;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC_Door;

#pragma endregion

#pragma region Trigger

private:
	UFUNCTION()
	void OnCloseTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBoxComponent> CloseTrigger;

#pragma endregion

#pragma region SpotLight

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USpotLightComponent> SpotLight;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAudioComponent> AC_SpotLight;

#pragma endregion

};