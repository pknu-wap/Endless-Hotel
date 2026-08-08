// Copyright by 2026-1 WAP Game 2 team

#include "Player/Camera/EHPlayerCameraManager.h"
#include "Actor/Camera/EHCameraActor.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameFramework/Character.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "UI/HUD/Loading/UI_HUD_Loading.h"
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
	TimeLine_Loading = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine_Loading"));
}

void AEHPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	FindPPV();
	SetEyeEffect();

	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			OnChangedDataLayer(EMapDataLayer::Lobby);
		}), 0.1f, false);

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OnDataLayerChanged.AddUniqueDynamic(this, &ThisClass::OnChangedDataLayer);
}

#pragma endregion

#pragma region Data Layer

void AEHPlayerCameraManager::OnChangedDataLayer(const EMapDataLayer& DataLayer)
{
	auto* GameInstance = GetGameInstance<UEHGameInstance>();

	switch (DataLayer)
	{
	case EMapDataLayer::Hotel:
	{
		PossessCamera(Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
		if (bIsFirstHotel)
		{
			DM_EyeEffect->SetScalarParameterValue(FName("EyeEffect"), 0);
			StartEyeEffect(true);
			bIsFirstHotel = false;
		}
		break;
	}
	case EMapDataLayer::Lobby:
	{
		PossessCamera(ECameraType::Title);
		bIsFirstHotel = true;
		DM_EyeEffect->SetScalarParameterValue(FName("EyeEffect"), 5);
		break;
	}
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
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateWeakLambda(this, [this, bIsOpen]()
		{
			auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
			auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget());

			if (IsValid(UI_InGame) && UI_InGame->IsActivatedWidget())
			{
				if (bIsOpen)
				{
					UI_InGame->StartInGameHUD(true);
					TimeLine_Eye->PlayFromStart();
				}
				else
				{
					UI_InGame->StartInGameHUD(false);
					TimeLine_Eye->ReverseFromEnd();
				}

				auto* SoundCon = GetGameInstance()->GetSubsystem<USoundController>();
				SoundCon->FadeSFXSound(bIsOpen);

				FTimerHandle StopHandle;
				GetWorld()->GetTimerManager().SetTimer(StopHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
					{
						TimeLine_Eye->Stop();
					}), 6.f, false);

				GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
			}
		}), 0.01f, true);
}

void AEHPlayerCameraManager::LoadingEyeEffect()
{
	TimeLine_Loading->PlayFromStart();

	constexpr float StopDuration = 2.f;
	FTimerHandle StopHandle;
	GetWorld()->GetTimerManager().SetTimer(StopHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			TimeLine_Loading->Stop();
		}), StopDuration, false);
}

void AEHPlayerCameraManager::SetEyeEffect()
{
	DM_EyeEffect = UMaterialInstanceDynamic::Create(M_EyeEffect, this);

	PPV_EyeEffect->Settings.WeightedBlendables.Array.Empty();
	PPV_EyeEffect->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, DM_EyeEffect.Get()));

	FOnTimelineFloat Update_Open;
	Update_Open.BindUFunction(this, FName("OnValueChangedEyeEffect"));
	TimeLine_Eye->AddInterpFloat(CV_EyeOpen, Update_Open);

	FOnTimelineFloat Update_Loading;
	Update_Loading.BindUFunction(this, FName("OnValueChangedEyeEffect"));
	TimeLine_Loading->AddInterpFloat(CV_Loading, Update_Loading);
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

void AEHPlayerCameraManager::PossessCameraToPlayer(const float& BlendTime)
{
	PossessCamera(Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)), BlendTime);
}

#pragma endregion