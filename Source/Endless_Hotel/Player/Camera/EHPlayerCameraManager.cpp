// Copyright by 2026-1 WAP Game 2 team

#include "Player/Camera/EHPlayerCameraManager.h"
#include "Player/Character/EHPlayer.h"
#include "Actor/Camera/EHCameraActor.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Sound/SoundController.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/PostProcessVolume.h>
#include <Components/TimelineComponent.h>
#include <Camera/CameraComponent.h>

#pragma region Base

AEHPlayerCameraManager::AEHPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	TimeLine_EyeOpen = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine_EyeOpen"));
	TimeLine_EyeClose = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine_EyeClose"));
	TimeLine_Loading = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine_Loading"));

	ViewPitchMin = -70.0f;
	ViewPitchMax = 70.0f;
}

void AEHPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	FindPPV();
	SetEyeEffect();
	DM_EyeEffect->SetScalarParameterValue(FName("EyeEffect"), 5);

	GetWorld()->GetTimerManager().SetTimer(BindHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			if (auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
			{
				Player->OnDie.AddWeakLambda(this, [this](const EDeathReason&) {StartEyeEffect(false); });
				Player->OnRevive.AddWeakLambda(this, [this]() {StartEyeEffect(true); });
				GetWorld()->GetTimerManager().ClearTimer(BindHandle);
			}			
		}), 0.1f, true);
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
	bIsOpen ? TimeLine_EyeOpen->PlayFromStart() : TimeLine_EyeClose->PlayFromStart();

	auto* SoundCon = GetGameInstance()->GetSubsystem<USoundController>();
	SoundCon->FadeSFXSound(bIsOpen);
}

float AEHPlayerCameraManager::LoadingEyeEffect()
{
	TimeLine_Loading->PlayFromStart();

	return TimeLine_Loading->GetTimelineLength();
}

void AEHPlayerCameraManager::SetEyeEffect()
{
	DM_EyeEffect = UMaterialInstanceDynamic::Create(M_EyeEffect, this);

	PPV_EyeEffect->Settings.WeightedBlendables.Array.Empty();
	PPV_EyeEffect->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, DM_EyeEffect.Get()));

	FOnTimelineFloat Update_Open;
	Update_Open.BindUFunction(this, FName("OnValueChangedEyeEffect"));
	TimeLine_EyeOpen->AddInterpFloat(CV_EyeOpen, Update_Open);

	FOnTimelineFloat Update_Close;
	Update_Close.BindUFunction(this, FName("OnValueChangedEyeEffect"));
	TimeLine_EyeClose->AddInterpFloat(CV_EyeClose, Update_Close);

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
	if (!IsValid(CameraOwner))
	{
		return;
	}

	TimeLine_EyeOpen->Stop();
	TimeLine_EyeClose->Stop();
	TimeLine_Loading->Stop();

	DM_EyeEffect->SetScalarParameterValue(FName("EyeEffect"), 5);

	if (bIsPossessing)
	{
		WaitPossessTarget = CameraOwner;
		return;
	}

	WaitPossessTarget = nullptr;

	auto* PC = GetOwningPlayerController();
	PC->SetViewTargetWithBlend(CameraOwner, BlendTime, EViewTargetBlendFunction::VTBlend_EaseInOut, 2.5f);

	bIsPossessing = true;
	GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateWeakLambda(this, [this, BlendTime]()
		{
			bIsPossessing = false;
			PossessCamera(WaitPossessTarget.Get(), BlendTime);
		}), BlendTime + 0.01f, false);
}

void AEHPlayerCameraManager::PossessCameraToPlayer(const float& BlendTime)
{
	PossessCamera(Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)), BlendTime);
}

#pragma endregion

#pragma region Option

void AEHPlayerCameraManager::ActiveCameraShake(bool bActive)
{
	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	auto* Camera = Player->GetCamera();
	auto* Mesh = Player->GetMesh();

	if (bActive)
	{
		Camera->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("HeadSocket"));
		Camera->SetRelativeLocationAndRotation(FVector(7, 7, 0), FRotator::ZeroRotator);
		return;
	}

	Camera->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	Camera->SetRelativeLocationAndRotation(FVector(0, 30, 170), FRotator(0, 90, 0));
}

#pragma endregion