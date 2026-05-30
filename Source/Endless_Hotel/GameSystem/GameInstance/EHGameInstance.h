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
	
#pragma region Base

public:
	virtual void Init() override;

#pragma endregion

#pragma region Game

public:
	void QuitGame();

#pragma endregion

#pragma region Data

protected:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	TObjectPtr<class UPDA_Level> PDA_Map;

#pragma endregion

#pragma region Data Layer

public:
	// 로딩된 레이어을 활성화하고, 기존 레이어를 로드 상태로 변경
	void SwitchDataLayer(const EMapDataLayer& TargetDataLayer);

	// 위 함수의 로딩 있는 버전
	void SwitchDataLayerWithLoading(const EMapDataLayer& TargetDataLayer);

private:
	UDataLayerAsset* GetDataLayerAsset(const EMapDataLayer& Target);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataLayerChanged, const EMapDataLayer&, DataLayer);
	FOnDataLayerChanged OnDataLayerChanged;

private:
	FTimerHandle SwitchHandle;
	EMapDataLayer CurrentDataLayer = EMapDataLayer::Lobby;

#pragma endregion

#pragma region Demo Timer

public:
	void StartDemoTimer();

protected:
	UPROPERTY(EditAnywhere, Category = "DemoTimer")
	float GameplayTime = 0.f;

#pragma endregion

};