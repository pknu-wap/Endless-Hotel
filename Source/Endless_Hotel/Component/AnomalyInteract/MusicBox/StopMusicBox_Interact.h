// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/AnomalyInteract/AnomalyInteractComponent.h"
#include <CoreMinimal.h>
#include <StopMusicBox_Interact.generated.h>

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), EditInlineNew)
class ENDLESS_HOTEL_API UStopMusicBox_Interact : public UAnomalyInteractComponent
{
	GENERATED_BODY()
	
#pragma region Base

#pragma endregion

#pragma region Interact
	
public:
	virtual void SetAnomalyInteract() override;

	void StopMusicBox();

protected:
	virtual void Interacted_Implementation() override;

#pragma endregion

};
