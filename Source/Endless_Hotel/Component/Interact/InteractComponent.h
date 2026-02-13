// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include "Type/Interact/Type_Interact.h"
#include <CoreMinimal.h>
#include <InteractComponent.generated.h>

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRestoredSignature, AActor*, RestoredActor);

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

protected:
	UPROPERTY()
	TWeakObjectPtr<class AEHPlayer> Player;

	UPROPERTY()
	TWeakObjectPtr<class UWidgetComponent> Comp_Widget;

	UPROPERTY()
	TWeakObjectPtr<class UUI_Interact> UI_Interact;

#pragma endregion

#pragma region Interact

public:
	// 상호작용 UI를 보여주는 함수
	void ShowDescriptionWidget(bool bIsShow);

	// 상호작용 가능 여부 리턴 ( List_Interact에 아무것도 없어야 하고, 한번이라도 상호작용 X 이어야 함 )
	bool CanInteract();

	// 현재 선택된 상호작용 번호 변경
	void ChangeIndex(bool bUp);

	// 상호작용
	void Interact();

protected:
	// 현재 선택된 상호작용의 설명 텍스트 값 리턴
	FText GetDescription() { return List_Interact[CurrentIndex].Description; }

public:
	// 추가적으로 처리해야 하는 기능들을 여기에 집어넣기
	TFunction<void()> AdditionalAction;

protected:
	// 해당 물체에 할 수 있는 상호작용 리스트 ( 에디터에서 추가 )
	UPROPERTY(EditAnywhere, Category = "Interact")
	TArray<FInteractInfo> List_Interact;

	// 현재 선택된 상호작용 번호
	uint8 CurrentIndex = 0;

	// 해당 물체를 상호작용 했는지 여부
	bool bIsInteracted = false;

#pragma endregion

#pragma region Action

protected:
	void Action_Restore();
	void Action_Rotate();
	void Action_TurnOff();
	void Action_Burn();
	void Action_Elevator();

#pragma endregion

#pragma region Restore

public:
	void SaveOriginalTransform();
	void StartRestoring(float Duration = 2.5f);

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnRestoredSignature OnRestored;

private:
	void RestoreTick();
	void FinishRestoring();
	float RestoreDuration = 2.5f;
	float RestoreCurrentTime = 0.f;

public:
	FTransform OriginalTransform;
	FTransform StartTransform;
	FTimerHandle RestoreHandle;

#pragma endregion

};