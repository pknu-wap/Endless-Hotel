// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Lighter/Lighter.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Controller/EHPlayerController.h"
#include <Camera/CameraComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>
#include <Engine/PostProcessVolume.h>

#pragma region Base

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
	BlurBackground(true);
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

			BlurBackground(false);

			Destroy();
		}), 2, false);
}

#pragma endregion

#pragma region Blur

void ALighter::BlurBackground(bool bActive)
{
	APostProcessVolume* PPV = nullptr;

	for (TActorIterator<APostProcessVolume> Iter(GetWorld()); Iter; ++Iter)
	{
		if (Iter->ActorHasTag(TEXT("Highlight")))
		{
			PPV = *Iter;
			break;
		}
	}

	auto& Array_PPV = PPV->Settings.WeightedBlendables.Array;

	if (bActive)
	{
		DynMat_Blur = UMaterialInstanceDynamic::Create(Mat_Blur, this);

		Array_PPV.Add(FWeightedBlendable(1, DynMat_Blur));
	}
	else
	{
		for (int32 i = Array_PPV.Num() - 1; i >= 0; --i)
		{
			if (Array_PPV[i].Object == DynMat_Blur)
			{
				Array_PPV.RemoveAt(i);
			}
		}
	}
}

#pragma endregion