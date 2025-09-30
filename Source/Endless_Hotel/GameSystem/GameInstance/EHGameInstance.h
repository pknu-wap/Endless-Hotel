// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EHGameInstance.generated.h"

#pragma region Declare

UENUM(BlueprintType)
enum class EMapType : uint8
{
	None		UMETA(DisplayName = "None"),
	MainMenu	UMETA(DisplayName = "MainMenu"),
	Hotel		UMETA(DisplayName = "Hotel")
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UEHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void OnStart() override;

#pragma endregion

#pragma region Map

public:
	void OpenMap(const EMapType& MapName);
	void QuitGame();

public:
	static EMapType CurrentMap;

#pragma endregion

};