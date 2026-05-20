// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <Engine/GameInstance.h>
#include <EHGameInstance.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UEHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
#pragma region Game

public:
	void QuitGame();

#pragma endregion

#pragma region Data

protected:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	TObjectPtr<class UPDA_Level> PDA_Map;

#pragma endregion

#pragma region Level

public:
	void LoadLevel(const ELevelType& LevelType);
	void OpenLevel();

	// 타겟이 되는 레이어을 미리 로딩시킴
	void LoadDataLayer(const EHotelDataLayer& Layer);

	// 로딩된 레이어을 활성화하고, 기존 레이어를 언로드 시킴
	bool SwitchDataLayer();

private:
	UDataLayerAsset* GetDataLayerAsset(const EHotelDataLayer& Target);

public:
	ELevelType CurrentLevelType = ELevelType::MainMenu;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoaded);
	FOnLevelLoaded OnLevelLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelOpened, const ELevelType&, LevelType);
	FOnLevelOpened OnLevelOpened;

private:
	EHotelDataLayer LoadLayer = EHotelDataLayer::Hotel;
	EHotelDataLayer UnloadLayer = EHotelDataLayer::Hotel;

	UPROPERTY()
	TObjectPtr<UDataLayerAsset> TargetDataLayer;

#pragma endregion

};