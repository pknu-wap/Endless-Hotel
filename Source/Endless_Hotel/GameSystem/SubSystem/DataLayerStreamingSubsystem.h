// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Delegates/DelegateCombinations.h>
#include <DataLayerStreamingSubsystem.generated.h>

#pragma region Declare

class UDataLayerInstance;
class ULevelStreaming;
class ULevel;
class AAnomaly_Object_Base;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UDataLayerStreamingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region Data Layer

public:
	UFUNCTION()
	void OnChangedDataLayer(const EMapDataLayer& DataLayer);

	bool IsDataLayerVisited(const EMapDataLayer& DataLayer) const { return VisitedDataLayers.Contains(DataLayer); }
	EMapDataLayer GetCurrentDataLayer() const { return CurrentDataLayer; }
	void SetCurrentDataLayer(const EMapDataLayer& DataLayer) { CurrentDataLayer = DataLayer; }

	DECLARE_MULTICAST_DELEGATE(FOnDataLayerStreamingReady);
	FOnDataLayerStreamingReady OnDataLayerReady;

private:
	void WaitForDataLayerReady(const EMapDataLayer& DataLayer, bool bAlreadyRegistered);

private:
	UPROPERTY()
	TSet<EMapDataLayer> VisitedDataLayers;

	EMapDataLayer CurrentDataLayer = EMapDataLayer::Hotel;

	FTimerHandle DataLayerStreamingCheckHandle;

#pragma endregion

#pragma region Reset

public:
	void ResetDataLayerState();

#pragma endregion
};