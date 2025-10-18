// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EHPlayerController.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AEHPlayerController : public APlayerController
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AEHPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Input

protected:
	virtual void SetupInputComponent() override;

	void EscapeStarted(const struct FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> IMC_Default;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_ESC;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUI_PopUp_Base> UI_Escape;

#pragma endregion

};