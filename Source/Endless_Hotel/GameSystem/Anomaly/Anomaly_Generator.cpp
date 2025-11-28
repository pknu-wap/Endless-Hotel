// Anomaly_Generator.cpp

#include "Anomaly_Generator.h"
#include "Kismet/GameplayStatics.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

#pragma region Base

void AAnomaly_Generator::BeginPlay()
{
	Super::BeginPlay();

	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();

	uint8 IsNormal = FMath::RandRange(1, 10);
	if (IsNormal > 7)
	{
		SpawnNormal();
		return;
	}
	SpawnAnomalyAtIndex(Sub->ActIndex);
	Sub->ActIndex++;
}

#pragma endregion

#pragma region AnomalyObjectLinker

void AAnomaly_Generator::AnomalyObjectLinker()
{
	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();

	UClass* TargetClass = Sub->GetObjectByID(CurrentAnomaly->AnomalyID);

	if (!TargetClass)
	{
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetClass, OUT FoundActors);

	for (auto* FoundActor : FoundActors)
	{
		auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
		CurrentAnomaly->LinkedObjects.Add(FoundActor);
	}
}

#pragma endregion

#pragma region Generate

// Spawn Anomaly at Specific Index
AAnomaly_Base* AAnomaly_Generator::SpawnAnomalyAtIndex(uint8 Index)
{
	UE_LOG(LogTemp, Verbose, TEXT("[Gen %s] SpawnAnomalyAtIndex(%d)"), *GetName(), Index);

	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();

	// Out of Range Check
	if (!(Sub->ActAnomaly).IsValidIndex(Index))
	{
		if (Sub->ActAnomaly.Num() == 0)
		{
			return nullptr;
		}
		Index = 0;
		Sub->InitializePool();
		return SpawnAnomalyAtIndex(Index); // restart
	}

	TSubclassOf<AAnomaly_Base> AnomalyClass = Sub->ActAnomaly[Index].AnomalyClass;

	// Spawn
	const FTransform SpawnTransform(FVector::ZeroVector);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAnomaly_Base* Spawned =
		GetWorld()->SpawnActor<AAnomaly_Base>(AnomalyClass, SpawnTransform, Params);

	if (!Spawned)
	{
		return nullptr;
	}

	Spawned->AnomalyID = Sub->ActAnomaly[Index].AnomalyID;

	CurrentAnomaly = Spawned;

	AnomalyObjectLinker();

	// Start
	Spawned->ActivateAnomaly(Spawned->AnomalyID);

	// EventBroadCast
	OnAnomalySpawned.Broadcast(Spawned);

	return Spawned;
}

AAnomaly_Base* AAnomaly_Generator::SpawnNormal()
{
	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();

	TSubclassOf<AAnomaly_Base> AnomalyClass = NormalClass;

	// Spawn
	const FTransform SpawnTransform(FVector::ZeroVector);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAnomaly_Base* Spawned =
		GetWorld()->SpawnActor<AAnomaly_Base>(AnomalyClass, SpawnTransform, Params);

	if (!Spawned)
	{
		return nullptr;
	}

	CurrentAnomaly = Spawned;

	return Spawned;
}
#pragma endregion

#pragma region ForTest

void AAnomaly_Generator::AddAnomaly()
{
	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	for (const TSubclassOf<AAnomaly_Base>& AnomalyClass : OriginAnomaly)
	{
		AAnomaly_Base* CDO = AnomalyClass->GetDefaultObject<AAnomaly_Base>();
		const uint8 AnomalyID = CDO->AnomalyID;
		TSubclassOf<AAnomaly_Object_Base> ObjectClass = CDO->ObjectClass->GetClass();
		Sub->OriginAnomaly.Add(FAnomalyEntry{ AnomalyID, AnomalyClass, ObjectClass });
	}
}

#pragma endregion