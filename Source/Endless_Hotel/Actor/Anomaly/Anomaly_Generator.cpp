// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly_Generator.h"
#include "Anomaly/Base/Anomaly_Event.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Data/Controller/DataController.h"
#include <EngineUtils.h>

#pragma region AnomalyObject

void AAnomaly_Generator::AnomalyObjectLinker(const TArray<TSubclassOf<AAnomaly_Object_Base>>& TargetClasses)
{
	if (TargetClasses.IsEmpty())
	{
		return;
	}

	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	auto ObjectPool = Sub->GetAnomalyObject();

	const EAnomalyID TargetAnomalyName = static_cast<EAnomalyID>(CurrentAnomaly->AnomalyName);

	for (const auto& TargetClass : TargetClasses)
	{
		if (auto* FoundStruct = ObjectPool.Find(TargetClass.Get()))
		{
			for (auto& AnomalyObject : FoundStruct->Objects)
			{
				if (!IsValid(AnomalyObject))
				{
					continue;
				}
				if (AnomalyObject->ExecuteAnomalies.Contains(TargetAnomalyName))
				{
					AnomalyObject->AnomalyID = CurrentAnomaly->AnomalyName;
					AnomalyObject->SetAnomalyName();
					CurrentAnomaly->LinkedObjects.Add(AnomalyObject);
				}
			}
		}
	}
}

void AAnomaly_Generator::BeginPlay()
{
	Super::BeginPlay();
	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	Sub->FloorChange.AddDynamic(this, &ThisClass::SpawnAnomaly);
}

#pragma endregion

#pragma region Generate

void AAnomaly_Generator::SpawnAnomaly()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	int32 IsNormal = FMath::RandRange(1, 10);

	if (IsNormal > 8 || Subsystem->Floor == STARTFLOOR)
	{
		SpawnNormal(SpawnedLevel);
		return;
	}
	
	SpawnAnomalyAtIndex(Subsystem->ActIndex, SpawnedLevel);
	Subsystem->ActIndex++;
}

// Spawn Anomaly at Specific Index
AAnomaly_Event* AAnomaly_Generator::SpawnAnomalyAtIndex(uint8 Index, ULevel* SpawnLevel)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();

	// Out of Range Check
	if (!(DataC->ActAnomaly).IsValidIndex(Index))
	{
		Index = 0;
		Sub->InitializePool();
		return SpawnAnomalyAtIndex(Index, SpawnLevel); // restart
	}

	UE_LOG(LogTemp, Log, TEXT("[GameSystem] RemainAnomaly: %d"), DataC->GetRemainingAnomalyCounts());
	TSoftClassPtr<AAnomaly_Event> SoftAnomalyClass = DataC->ActAnomaly[Index].AnomalyClass;
	UClass* AnomalyClass = SoftAnomalyClass.LoadSynchronous();

	if (!IsValid(AnomalyClass))
	{
		FTimerHandle RetryHandle;
		GetWorld()->GetTimerManager().SetTimer(RetryHandle, FTimerDelegate::CreateWeakLambda(this, [this, Index, SpawnLevel]()
			{
				this->SpawnAnomalyAtIndex(Index, SpawnLevel);
			}), 0.5f, false);

		return nullptr;
	}

	UE_LOG(LogTemp, Warning, TEXT("클래스 이름: %s"), *AnomalyClass->GetName());

	// 이거 상혁이형이 한대로 수정하기
	const FTransform SpawnTransform(FVector::ZeroVector);

	FActorSpawnParameters Params;
	Params.OverrideLevel = SpawnLevel;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAnomaly_Event* Spawned = GetWorld()->SpawnActor<AAnomaly_Event>(AnomalyClass, SpawnTransform, Params);

	if (!Spawned)
	{
		return nullptr;
	}

	Spawned->AnomalyName = DataC->ActAnomaly[Index].AnomalyID;
	CurrentAnomaly = Spawned;

	TArray<TSubclassOf<AAnomaly_Object_Base>> TargetClasses = DataC->GetObjectByID(CurrentAnomaly->AnomalyName);
	AnomalyObjectLinker(TargetClasses);

	// Start
	CurrentAnomaly->SetAnomalyState();

	// EventBroadCast
	Sub->CurrentAnomalyID = CurrentAnomaly->AnomalyName;
	Sub->CurrentAnomaly = CurrentAnomaly;
	Sub->SetTargetElevator();
	Sub->OnAnomalySpawned.Broadcast();

	return CurrentAnomaly;
}

AAnomaly_Event* AAnomaly_Generator::SpawnNormal(ULevel* SpawnLevel)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();

	UClass* AnomalyClass = NormalClass.LoadSynchronous();
	// Spawn
	const FTransform SpawnTransform(FVector::ZeroVector);

	FActorSpawnParameters Params;
	Params.OverrideLevel = SpawnLevel;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAnomaly_Event* Spawned = GetWorld()->SpawnActor<AAnomaly_Event>(AnomalyClass, SpawnTransform, Params);

	if (!Spawned)
	{
		return nullptr;
	}

	CurrentAnomaly = Spawned;
	Sub->CurrentAnomaly = Spawned;
	Sub->SetTargetElevator();
	Sub->OnAnomalySpawned.Broadcast();

	return Spawned;
}

#pragma endregion