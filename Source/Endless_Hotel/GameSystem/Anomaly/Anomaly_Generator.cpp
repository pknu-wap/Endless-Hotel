// Anomaly_Generator.cpp

#include "Anomaly_Generator.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/PlatformTime.h"
#include "Misc/DateTime.h"
#include "Misc/Guid.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <GameSystem/SubSystem/AnomalyProgressSubSystem.h>

#pragma region Base

AAnomaly_Generator::AAnomaly_Generator(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAnomaly_Generator::BeginPlay()
{
	Super::BeginPlay();

	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Sub->GetAnomalyData();
	Sub->InitializePool(true);

	// Check AnomalyID Settings
	TSet<uint8> UsedID;
	for (auto AnomalyClass : Sub->ActAnomaly)
	{
		if (!AnomalyClass.ID) continue;
		const AAnomaly_Base* CDO = AnomalyClass.Class->GetDefaultObject<AAnomaly_Base>();
		const uint8 FixedID = CDO ? CDO->AnomalyID : -1;
	}
}

#pragma endregion

#pragma region AnomalyObjectLinker

void AAnomaly_Generator::AnomalyObjectLinker()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Base::StaticClass(), OUT FoundActors);

	for (auto* FoundActor : FoundActors)
	{
		auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
		auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
		uint8 LinkObjectID = Sub->GetAnomalyDataByID(CurrentAnomaly->AnomalyID);
		if(LinkObjectID == AnomalyObject->ObjectID)
			CurrentAnomaly->LinkedObjects.Add(AnomalyObject);
	}
}

#pragma endregion

#pragma region Generate

bool AAnomaly_Generator::DestroyCurrentAnomaly()
{
	if (CurrentAnomaly.IsValid())
	{
		
		UE_LOG(LogTemp, Log, TEXT("[Anomaly_Generator] Destroying %s"), *CurrentAnomaly->GetName());
		CurrentAnomaly->Destroy();
		CurrentAnomaly = nullptr;
		return true;
	}
	return false;
}

// Spawn Anomaly at Specific Index
AAnomaly_Base* AAnomaly_Generator::SpawnAnomalyAtIndex(int32 Index, bool bDestroyPrev)
{
	UE_LOG(LogTemp, Verbose, TEXT("[Gen %s] SpawnAnomalyAtIndex(%d)"), *GetName(), Index);

	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();

	// Out of Range Check
	if (!(Sub->ActAnomaly).IsValidIndex(Index))
	{
		Sub->InitializePool(true);
		Sub->ActIndex = 0; // restart
	}

	// Destroy Previous
	if (bDestroyPrev)
	{
		DestroyCurrentAnomaly();
	}

	const FAnomalyEntry& ActingAnomaly = Sub->ActAnomaly[Index];

	// Spawn
	const FTransform SpawnTransform(FVector::ZeroVector);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAnomaly_Base* Spawned = GetWorld()->SpawnActor<AAnomaly_Base>(ActingAnomaly.Class, SpawnTransform, Params);

	if (!Spawned)
	{
		return nullptr;
	}
	Spawned->AnomalyID = ActingAnomaly.ID;
	CurrentAnomaly = Spawned;

	// Start
	Spawned->ActivateAnomaly(Spawned->AnomalyID);

	AnomalyObjectLinker();

	// EventBroadCast
	OnAnomalySpawned.Broadcast(Spawned);

	return Spawned;
}

#pragma endregion