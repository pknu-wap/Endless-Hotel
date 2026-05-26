// Copyright by 2026-1 WAP Game 2 team

#include "Player/Camera/EHPlayerCameraManager.h"
#include "Actor/Camera/EHCameraActor.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Camera/PDA_Camera.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "Sound/SoundController.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/PostProcessVolume.h>
#include <Components/TimelineComponent.h>

#pragma region Base

AEHPlayerCameraManager::AEHPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	TimeLine_Eye = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine_Eye"));
}

void AEHPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	FindPPV();
	LoadCameraDataAsset();
}

#pragma endregion

#pragma region Data

void AEHPlayerCameraManager::LoadCameraDataAsset()
{
	TArray<FPrimaryAssetId> DataIDs;

	auto& AssetManager = UEHAssetManager::Get();
	AssetManager.GetPrimaryAssetIdList(FPrimaryAssetType("Camera"), OUT DataIDs);

	FPrimaryAssetId DataID = DataIDs[0];
	AssetManager.LoadPrimaryAsset(DataID, { FName("EyeEffect") }, FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoadedCameraDataAsset, DataID));
}

void AEHPlayerCameraManager::OnLoadedCameraDataAsset(FPrimaryAssetId DataAssetID)
{
	auto& AssetManager = UEHAssetManager::Get();
	auto* DataAsset = AssetManager.GetPrimaryAssetObject<UPDA_Camera>(DataAssetID);

	DM_EyeEffect = UMaterialInstanceDynamic::Create(DataAsset->M_EyeEffect.LoadSynchronous(), this);

	PPV_EyeEffect->Settings.WeightedBlendables.Array.Empty();
	PPV_EyeEffect->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, DM_EyeEffect.Get()));

	FOnTimelineFloat Update_Open;
	Update_Open.BindUFunction(this, FName("OnValueChangedEyeEffect"));
	TimeLine_Eye->AddInterpFloat(DataAsset->CV_EyeOpen.LoadSynchronous(), Update_Open);

	auto* GameInstance = GetGameInstance<UEHGameInstance>();

	switch (GameInstance->CurrentLevelType)
	{
	case ELevelType::Hotel:
		PossessCamera(Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
		StartEyeEffect(true);
		break;

	case ELevelType::MainMenu:
		PossessCamera(ECameraType::Title);
		DM_EyeEffect->SetScalarParameterValue(FName("EyeEffect"), 5);
		break;
	}
}

#pragma endregion

#pragma region Post Processing

void AEHPlayerCameraManager::FindPPV()
{
	for (auto* Target : GetWorld()->PostProcessVolumes)
	{
		auto* PPV = Cast<APostProcessVolume>(Target);
		if (IsValid(PPV) && PPV->ActorHasTag(FName("Eye")))
		{
			PPV_EyeEffect = PPV;
			break;
		}
	}
}

#pragma endregion

#pragma region Eye

void AEHPlayerCameraManager::StartEyeEffect(bool bIsOpen)
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();

	auto* UICon = GameInstance->GetSubsystem<UUI_Controller>();
	auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget());

	auto* SoundCon = GameInstance->GetSubsystem<USoundController>();
	SoundCon->FadeSFXSound(bIsOpen);

	if (bIsOpen)
	{
		TimeLine_Eye->PlayFromStart();
	}
	else
	{
		UI_InGame->EyeEffectBlur(false);
		TimeLine_Eye->ReverseFromEnd();
	}

	FTimerHandle StopHandle;
	GetWorld()->GetTimerManager().SetTimer(StopHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			TimeLine_Eye->Stop();
		}), 5.f, false);
}

void AEHPlayerCameraManager::OnValueChangedEyeEffect(float Value)
{
	DM_EyeEffect->SetScalarParameterValue(FName("EyeEffect"), Value);
}

#pragma endregion

#pragma region Possess

void AEHPlayerCameraManager::PossessCamera(const ECameraType& CameraType, const float& BlendTime)
{
	auto* TargetCamera = Cameras.Find(CameraType);

	PossessCamera(TargetCamera->Get(), BlendTime);
}

void AEHPlayerCameraManager::PossessCamera(AActor* CameraOwner, const float& BlendTime)
{
	auto* PC = GetOwningPlayerController();
	PC->SetViewTargetWithBlend(CameraOwner, BlendTime);
}

#pragma endregion