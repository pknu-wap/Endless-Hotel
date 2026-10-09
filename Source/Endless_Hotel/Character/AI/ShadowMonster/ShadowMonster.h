// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAI.h"
#include <CoreMinimal.h>
#include <ShadowMonster.generated.h>

#pragma region Declare

class UShadowMonsterAnimInstance;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AShadowMonster : public ABaseAI
{
	GENERATED_BODY()

#pragma region Appear
	
public:
	void StartAppear();
	
private:
	UShadowMonsterAnimInstance* GetShadowAnim() const;
	
private:
	bool bIsAppearing = false;
	
	UPROPERTY(EditAnywhere, Category = "Appear", meta = (ClampMin = "0.0"))
	float AppearRootMotionScale = 0.5f;
	
#pragma endregion
	
};