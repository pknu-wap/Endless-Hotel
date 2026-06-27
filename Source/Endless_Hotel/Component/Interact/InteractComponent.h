// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include "Type/Interact/Type_Interact.h"
#include <CoreMinimal.h>
#include <InteractComponent.generated.h>

#pragma region Declare

#define HIGHLIGHT_TAG TEXT("Highlight")

#pragma endregion

UCLASS(ClassGroup = (Custom))
class ENDLESS_HOTEL_API UInteractComponent : public UEHComponent
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Reference

private:
	UPROPERTY()
	TWeakObjectPtr<class UUI_Interact> UI_Interact;

#pragma endregion

#pragma region Interact

public:
	// 상호작용 가능 여부 시각 확인 함수
	void ShowInteracting(bool bIsShow);

	// 상호작용 가능 여부 리턴 ( List_Interact에 하나라도 있어야 하고, 한 번이라도 상호작용 X 이어야 함 )
	bool CanInteract() { return !List_Interact.IsEmpty() && !bIsInteracted; }

	// 현재 선택된 상호작용 번호 변경
	void ChangeIndex(bool bUp);

	// 상호작용
	void Interact(class AEHCharacter* Interacter);

	// 현재 선택된 상호작용 정보 가져오는 함수
	FInteractInfo GetSelectedInteractInfo();

	// 상호작용을 다시 할 수 있게 해주는 함수
	void RestoreInteract() { bIsInteracted = false; }

private:
	// 상호작용 UI를 보여주는 함수
	void ShowDescriptionWidget(bool bIsShow);

	// 현재 선택된 상호작용의 설명 텍스트 값 리턴
	FText GetDescription() { return List_Interact[CurrentIndex].Description; }

public:
	// 해당 물체에 할 수 있는 상호작용 리스트 ( 에디터에서 추가 )
	UPROPERTY(EditAnywhere, Category = "Interact")
	TArray<FInteractInfo> List_Interact;

private:
	// 해당 물체를 한번이라도 상호작용 했는지 여부
	bool bIsInteracted = false;

	// 현재 선택된 상호작용 번호
	int8 CurrentIndex = 0;

#pragma endregion

#pragma region Highlight

public:
	// 상호작용 윤곽선을 보여주는 함수
	void ShowInteractingHighlight(bool bActive);

#pragma endregion

};