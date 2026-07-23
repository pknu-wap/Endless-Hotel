// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Character/EHCharacter.h"
#include <CoreMinimal.h>
#include <BaseAI.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ABaseAI : public AEHCharacter
{
	GENERATED_BODY()

#pragma region Base

public:
	ABaseAI(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Navigation

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Navigation)
	TObjectPtr<class UNavigationInvokerComponent> NavInvoker;

	UPROPERTY(EditAnywhere, Category = Navigation)
	float NavGenerationRadius = 3000.f;

	UPROPERTY(EditAnywhere, Category = Navigation)
	float NavRemovalRadius = 5000.f;

#pragma endregion

};