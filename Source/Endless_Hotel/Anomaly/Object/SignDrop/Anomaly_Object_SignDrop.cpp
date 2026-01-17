// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/SignDrop/Anomaly_Object_SignDrop.h"
#include "RoomSign/RoomSignActor.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

AAnomaly_Object_SignDrop::AAnomaly_Object_SignDrop(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void AAnomaly_Object_SignDrop::BeginPlay()
{
	Super::BeginPlay();

	RoomSigns.Empty();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ARoomSignActor::StaticClass(),
		FoundActors
	);

	for (AActor* Actor : FoundActors)
	{
		if (ARoomSignActor* Sign = Cast<ARoomSignActor>(Actor))
		{
			RoomSigns.Add(Sign);
		}
	}
}
#pragma endregion

#pragma region Drop

void AAnomaly_Object_SignDrop::ExecuteSignDrop()
{
    if (RoomSigns.Num() == 0) return;

    int32 RandomIndex = FMath::RandRange(0, RoomSigns.Num() - 1);
    ARoomSignActor* TargetSign = RoomSigns[RandomIndex];

    if (!TargetSign) return;

    TargetSign->DropSign();
    RoomSigns.RemoveAt(RandomIndex);
}

#pragma endregion