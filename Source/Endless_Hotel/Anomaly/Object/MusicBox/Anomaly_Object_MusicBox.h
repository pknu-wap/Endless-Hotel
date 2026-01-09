// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_MusicBox.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_MusicBox : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_MusicBox(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, Category = "BoxBody")
	TObjectPtr<class UStaticMeshComponent> Mesh_BoxBody;

	UPROPERTY(EditAnywhere, Category = "BoxBody")
	TObjectPtr<class UStaticMeshComponent> Mesh_BoxRotator;

#pragma endregion

#pragma region Sound

protected:
	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_MusicBox;

#pragma endregion


#pragma region PlayMusicBox

public:
	void PlayMusicBox();

protected:
	UPROPERTY(EditAnywhere, Category = "MusicBox|Fail");
	FTimerHandle FailTimerHandle;

	UPROPERTY(EditAnywhere, Category = "MusicBox|Fail");
	float LimitTime;

#pragma endregion


#pragma region Interact

public:
	virtual void SetInteraction() override;

protected:
	virtual void Interacted_Implementation() override;
	void StopMusicBox();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "MusicBox|Interact")
	bool bWaitingInteract = false;

#pragma endregion

};
