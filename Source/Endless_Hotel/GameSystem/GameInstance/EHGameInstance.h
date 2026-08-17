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
	void SwitchDataLayer(const EMapDataLayer& TargetDataLayer, bool bNotifyDelegate = true);
	void ActiveAdditionalDataLayer(const EMapDataLayer& TargetDataLayer, bool bActive);

	const EMapDataLayer& GetCurrentDataLayer() { return CurrentDataLayer; }
	UDataLayerInstance* GetDataLayerInstance(const EMapDataLayer& Target);

private:
	UDataLayerAsset* GetDataLayerAsset(const EMapDataLayer& Target);

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataLayerChanged, const EMapDataLayer&);
	FOnDataLayerChanged OnDataLayerChanged;

private:
	EMapDataLayer CurrentDataLayer = EMapDataLayer::Lobby;

#pragma endregion

};