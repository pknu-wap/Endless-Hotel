// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/DataLayerStreamingSubsystem.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include <WorldPartition/WorldPartitionSubsystem.h>
#include <WorldPartition/DataLayer/DataLayerInstance.h>
#include <Engine/World.h>
#include <Engine/GameInstance.h>
#include <TimerManager.h>

#pragma region Base

void UDataLayerStreamingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (UEHGameInstance* GameInstance = Cast<UEHGameInstance>(GetGameInstance()))
	{
		GameInstance->OnDataLayerChanged.AddUObject(this, &ThisClass::OnChangedDataLayer);
	}
}

#pragma endregion

#pragma region Data Layer

void UDataLayerStreamingSubsystem::OnChangedDataLayer(const EMapDataLayer& DataLayer)
{
	UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr;
	if (!World)
	{
		if (UGameInstance* GI = GetGameInstance())
		{
			GI->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(this,
				[this, DataLayer]() { OnChangedDataLayer(DataLayer); }));
		}
		return;
	}

	WaitForDataLayerReady(DataLayer, VisitedDataLayers.Contains(DataLayer));
}

void UDataLayerStreamingSubsystem::WaitForDataLayerReady(const EMapDataLayer& DataLayer, bool bAlreadyRegistered)
{
	UWorld* World = GetWorld();
	UEHGameInstance* GameInstance = Cast<UEHGameInstance>(GetGameInstance());
	const UDataLayerInstance* TargetInstance = GameInstance ? GameInstance->GetDataLayerInstance(DataLayer) : nullptr;

	if (!World || !TargetInstance)
	{
		return;
	}

	TWeakObjectPtr<UWorld> WeakWorld = World;

	World->GetTimerManager().SetTimer(DataLayerStreamingCheckHandle, FTimerDelegate::CreateWeakLambda(this,
		[this, WeakWorld, DataLayer, TargetInstance]()
		{
			UWorld* SafeWorld = WeakWorld.Get();
			if (!SafeWorld)
			{
				return;
			}
			UWorldPartitionSubsystem* WPSubsystem = SafeWorld->GetSubsystem<UWorldPartitionSubsystem>();
			if (!WPSubsystem || !WPSubsystem->IsStreamingCompleted())
			{
				return;
			}

			SafeWorld->GetTimerManager().ClearTimer(DataLayerStreamingCheckHandle);
			VisitedDataLayers.Add(DataLayer);
			CurrentDataLayer = DataLayer;
			OnDataLayerReady.Broadcast();
		}), 0.1f, true);
}

#pragma endregion

#pragma region Reset

void UDataLayerStreamingSubsystem::ResetDataLayerState()
{
	VisitedDataLayers.Empty();
	CurrentDataLayer = EMapDataLayer::Hotel;

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(DataLayerStreamingCheckHandle);
	}
}

#pragma endregion