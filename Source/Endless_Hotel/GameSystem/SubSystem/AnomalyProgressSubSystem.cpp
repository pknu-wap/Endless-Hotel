// Copyright by 2025-2 WAP Game 2 team

#include "AnomalyProgressSubSystem.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"

#pragma region Base

UAnomalyProgressSubSystem::UAnomalyProgressSubSystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> AnomalyFinder(TEXT("/Game/EndlessHotel/Data/DT_AnomalyData.DT_AnomalyData"));
	if (AnomalyFinder.Succeeded())
	{
		DataTable_Anomaly = AnomalyFinder.Object;
	}

	GameClearEvent.AddDynamic(this, &ThisClass::GameClear);
}

void UAnomalyProgressSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Floor = 9;
	AnomalyCount = 0;
	ActIndex = 0;
	GetAnomalyData();
	InitializePool();
}
#pragma endregion

#pragma region Verdict

bool UAnomalyProgressSubSystem::ComputeVerdict(bool bSolved, bool bNormalElevator) const
{
	switch (VerdictMode)
	{
	case EAnomalyVerdictMode::AnomalyElevatorOnly:
		return !bNormalElevator;
	case EAnomalyVerdictMode::SolvedOnly:
		return bSolved;
	case EAnomalyVerdictMode::Both_AND:
		return bSolved && !bNormalElevator;
	case EAnomalyVerdictMode::Normal:
		return !bSolved && bNormalElevator;
	default:
		return false;
	}
}

void UAnomalyProgressSubSystem::ApplyVerdict()
{
	const bool bPassed = ComputeVerdict(bIsAnomalySolved, bIsElevatorNormal);
	UE_LOG(LogTemp, Log, TEXT("[Verdict] Verdict Mode is %s, Verdict Result is %s"),
		*UEnum::GetValueAsString(VerdictMode), bPassed ? TEXT("Pass") : TEXT("FAIL"))
	if (bPassed) 
	{
		SubFloor();
		if(!AnomalyHistory.Contains(CurrentAnomalyID))
		{
			AnomalyHistory.Add(CurrentAnomalyID);
		}
		AnomalyCount++;
	}
	else 
	{ 
		ResetFloor();
	}
	bIsAnomalySolved = false;

	if (!bIsClear)
	{
		UEHGameInstance* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
		GameInstance->OpenMap(EMapType::Hotel);
	}
}

#pragma endregion

#pragma region Floor

void UAnomalyProgressSubSystem::SubFloor()
{
	if (Floor > 2)
	{
		Floor--;
	}
	else
	{
		GameClearEvent.Broadcast();
	}
}

void UAnomalyProgressSubSystem::AddFloor()
{
	if (Floor < 8)
	{
		Floor++;
	}
}

#pragma endregion

#pragma region AnomalyDataBase

void UAnomalyProgressSubSystem::GetAnomalyData()
{
	FAnomalyData* Data = nullptr;

	for (auto RowData : DataTable_Anomaly->GetRowMap())
	{
		Data = (FAnomalyData*)RowData.Value;

		if (!Data->AnomalyPath.IsEmpty())
		{
			UClass* LoadedClass = StaticLoadClass(AAnomaly_Base::StaticClass(), nullptr, *Data->AnomalyPath);
			UClass* ObjectClass = StaticLoadClass(AAnomaly_Object_Base::StaticClass(), nullptr, *Data->ObjectPath);

			if (LoadedClass)
			{
				OriginAnomaly.Add(FAnomalyEntry{ Data->AnomalyID, LoadedClass, ObjectClass});
			}
		}
	}
}

TSubclassOf<AAnomaly_Object_Base> UAnomalyProgressSubSystem::GetObjectByID(uint8 AnomalyID)
{
	for (auto& Pair : DataTable_Anomaly->GetRowMap())
	{
		const FAnomalyData* Row = reinterpret_cast<const FAnomalyData*>(Pair.Value);
		if (Row->AnomalyID == AnomalyID)
		{
			UClass* LoadedClass = StaticLoadClass(AAnomaly_Object_Base::StaticClass(), nullptr, *Row->ObjectPath);
			return LoadedClass;
		}
	}
	return nullptr;
}

TSubclassOf<AAnomaly_Object_Base> UAnomalyProgressSubSystem::GetObjectByName(FString ObjectName)
{
	for (auto& Pair : DataTable_Anomaly->GetRowMap())
	{
		const FAnomalyData* Row = reinterpret_cast<const FAnomalyData*>(Pair.Value);
		if (Row->Anomaly_En == ObjectName)
		{
			UClass* LoadedClass = StaticLoadClass(AAnomaly_Object_Base::StaticClass(), nullptr, *Row->ObjectPath);
			return LoadedClass;
		}
	}
	return nullptr;
}

TSubclassOf<AAnomaly_Object_Base> UAnomalyProgressSubSystem::GetObjectByRowIndex(uint8 RowIndex)
{
	if (const FAnomalyData* Data = DataTable_Anomaly->FindRow<FAnomalyData>(*FString::FromInt(RowIndex), TEXT("")))
	{
		UClass* LoadedClass = StaticLoadClass(AAnomaly_Object_Base::StaticClass(), nullptr, *Data->ObjectPath);
		return LoadedClass;
	}
	return nullptr;
}

#pragma endregion

#pragma region Pool & Reset

void UAnomalyProgressSubSystem::InitializePool()
{
	// Copy from Original
	ActAnomaly = OriginAnomaly;

	ActIndex = 0;
	// Shuffle
	if (ActAnomaly.Num() > 1)
	{
		for (uint8 CurrentIndex = ActAnomaly.Num() - 1; CurrentIndex > 0; --CurrentIndex)
		{
			const uint8 RandomIndex = FMath::RandRange(0, CurrentIndex);
			if (CurrentIndex != RandomIndex)
			{
				ActAnomaly.Swap(CurrentIndex, RandomIndex);
			}
		}
	}

	// Reset Index
	ActIndex = 0;
}

#pragma endregion

#pragma region Clear

void UAnomalyProgressSubSystem::GameClear()
{
	// USaveManager에 로드 세이브 데이터로 클리어 여부 가져올 수 있음
	bIsClear = true;		// 게임 최초 클리어인지 판단용 bool 변수 -> 진행상황 리셋 추가 시 해당 변수 사용 예정
	//Initialize();
	//Todo:

	USaveManager::SaveGameClearData();
}

#pragma endregion