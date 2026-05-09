// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Camera/Type_Camera.h"
#include <CoreMinimal.h>
#include <Camera/CameraActor.h>
#include <EHCameraActor.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AEHCameraActor : public ACameraActor
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Register

private:
	void RegisterCamera();

protected:
	UPROPERTY(EditAnywhere, Category = "Info")
	ECameraType CameraType = ECameraType::None;

#pragma endregion

};