// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Components/ActorComponent.h>
#include <EHComponent.generated.h>

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESS_HOTEL_API UEHComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Base

public:
	UEHComponent(const FObjectInitializer& ObjectInitializer);

#pragma endregion

};