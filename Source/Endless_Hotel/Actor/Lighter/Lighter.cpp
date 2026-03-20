// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Lighter/Lighter.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Controller/EHPlayerController.h"
#include <Components/WidgetComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

ALighter::ALighter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Lighter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Lighter"));
	SetRootComponent(SM_Lighter);

	Component_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Component_Widget"));
	Component_Widget->SetupAttachment(RootComponent);

	Component_Interact = CreateDefaultSubobject<UInteractComponent>(TEXT("Component_Interact"));
}

void ALighter::BeginPlay()
{
	Super::BeginPlay();

	if (USaveManager::LoadTutorialData().bHasFlash)
	{
		Destroy();
		return;
	}
}

#pragma endregion

#pragma region Interact

void ALighter::Interact_Implementation(AEHCharacter* Interacter)
{
	SaveTutorialData();
	MoveToPlayerCamera(Interacter);
}

#pragma endregion

#pragma region Data

void ALighter::SaveTutorialData()
{
	FSaveData_Tutorial Data = USaveManager::LoadTutorialData();
	Data.bHasFlash = true;
	USaveManager::SaveTutorialData(Data);
}

#pragma endregion

#pragma region Move

void ALighter::MoveToPlayerCamera(AEHCharacter* Interacter)
{
	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetPlayerInputAble(false);

	auto* CameraComp = Interacter->FindComponentByClass<UCameraComponent>();

	FVector CameraLocation = CameraComp->GetComponentLocation();
	FVector ForwardVector = CameraComp->GetForwardVector();
	FVector UpVector = CameraComp->GetUpVector();
	constexpr float ForwardLength = 10.f;
	constexpr float UpLength = -3.f;

	FVector TargetLocation = CameraLocation + ForwardVector * ForwardLength + UpVector * UpLength;
	FRotator TargetRotation = GetActorRotation();
	TargetRotation.Roll += 25;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 0;
	LatentInfo.ExecutionFunction = FName("OnMoveCompleted");

	UKismetSystemLibrary::MoveComponentTo(RootComponent, TargetLocation, TargetRotation, true, true, 0.5f, false, EMoveComponentAction::Move, LatentInfo);
}

void ALighter::OnMoveCompleted()
{
	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			PC->SetPlayerInputAble(true);

			Destroy();
		}), 2, false);
}

#pragma endregion