// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Door/LobbyDoor.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/EHGameSystem.h"
#include "Player/Character/EHPlayer.h"
#include "UI/Controller/UI_Controller.h"
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SpotLightComponent.h>
#include <Components/RectLightComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/ExponentialHeightFogComponent.h>
#include <Components/PostProcessComponent.h>
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

ALobbyDoor::ALobbyDoor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CloseTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CloseTrigger"));
	SetRootComponent(CloseTrigger);
	CloseTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCloseTrigger);

	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	DoorLeft->SetupAttachment(RootComponent);

	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	DoorRight->SetupAttachment(RootComponent);

	AC_Door = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Door"));
	AC_Door->SetupAttachment(RootComponent);
	AC_Door->SetAutoActivate(false);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);
	SpotLight->SetVisibility(false);

	EndingFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("EndingFog"));
	EndingFog->SetupAttachment(RootComponent);
	EndingFog->SetFogDensity(0.f);

	AC_SpotLight = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_SpotLight"));
	AC_SpotLight->SetupAttachment(SpotLight);
	AC_SpotLight->SetAutoActivate(false);

	RectLight = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLight"));
	RectLight->SetupAttachment(RootComponent);
	RectLight->SetIntensity(0.f);

	TL_Rect = CreateDefaultSubobject<UTimelineComponent>(TEXT("TL_Rect"));

	PostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcess->BlendWeight = 0.f;

	FPostProcessSettings& Settings = PostProcess->Settings;
	Settings.bOverride_BloomIntensity = true;
	Settings.BloomIntensity = 0.675f;
	Settings.bOverride_AutoExposureMethod = true;
	Settings.AutoExposureMethod = EAutoExposureMethod::AEM_Manual;
	Settings.bOverride_AutoExposureBias = true;
	Settings.AutoExposureBias = 0.0f;

	Object->SetupAttachment(RootComponent);
}

void ALobbyDoor::BeginPlay()
{
	Super::BeginPlay();

	LeftCloseRot = DoorLeft->GetRelativeRotation();
	RightCloseRot = DoorRight->GetRelativeRotation();

	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	GameSystem->OnProgressionChanged.AddUObject(this, &ThisClass::OnChangedProgression);

	bool bActive = USaveManager::LoadData_Progression().Progression != EGameProgression::CheckIn;
	Component_Interact->ActiveInteract(bActive);

	FOnTimelineFloat UpdateRectLight;
	UpdateRectLight.BindUFunction(this, FName("OnUpdateRectLight"));
	TL_Rect->AddInterpFloat(CV_Rect, UpdateRectLight);

	FOnTimelineEvent FinishedRect;
	FinishedRect.BindUFunction(this, FName("OnFinishedRectLight"));
	TL_Rect->SetTimelineFinishedFunc(FinishedRect);
}

void ALobbyDoor::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	EndingFog->SetFogDensity(0.f);

	Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Progression

void ALobbyDoor::OnChangedProgression(EGameProgression Target)
{
	bool bActive = Target != EGameProgression::CheckIn;
	Component_Interact->ActiveInteract(bActive);
}

#pragma endregion

#pragma region Interact

void ALobbyDoor::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();
	switch (Info.InteractType)
	{
	case EInteractType::DoorOpen:
		constexpr float Duration = 4.f;
		RotateDoor(LeftOpenRot, RightOpenRot, SW_DoorOpen, Duration);
		break;
	}

	if (USaveManager::LoadData_Progression().Progression == EGameProgression::Clear_True)
	{
		CloseTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FPostProcessSettings& Settings = PostProcess->Settings;
		PostProcess->BlendWeight = 1.f;

		TL_Rect->PlayFromStart();

		auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
		UICon->OpenWidget(EWidgetType::PopUp_White);
	}
}

#pragma endregion

#pragma region Door

void ALobbyDoor::RotateDoor(FRotator LeftRot, FRotator RightRot, USoundWave* DoorSound, float Duration)
{
	FLatentActionInfo LatentInfo;
	LatentInfo.UUID = __LINE__;
	LatentInfo.CallbackTarget = this;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::MoveComponentTo(DoorLeft, DoorLeft->GetRelativeLocation(), LeftRot, true, true, Duration, true, EMoveComponentAction::Move, LatentInfo);

	LatentInfo.UUID = __LINE__;
	UKismetSystemLibrary::MoveComponentTo(DoorRight, DoorRight->GetRelativeLocation(), RightRot, true, true, Duration, true, EMoveComponentAction::Move, LatentInfo);

	AC_Door->SetSound(DoorSound);
	AC_Door->Play();
}

#pragma endregion

#pragma region Trigger

void ALobbyDoor::OnCloseTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto* Player = Cast<AEHPlayer>(OtherActor);
	if (!IsValid(Player))
	{
		return;
	}

	CloseTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	constexpr float Duration = 0.5f;
	RotateDoor(LeftCloseRot, RightCloseRot, SW_DoorClose, Duration);

	SpotLight->SetVisibility(true);
	EndingFog->SetFogDensity(1.f);
	AC_SpotLight->Play();
}

#pragma endregion

#pragma region SpotLight

void ALobbyDoor::OnUpdateRectLight(float Value)
{
	float Alpha = FMath::Clamp(Value, 0.0f, 1.0f);
	constexpr float Intensity = 400000.f;

	RectLight->SetIntensity(Alpha * Intensity);

	FPostProcessSettings& Settings = PostProcess->Settings;
	Settings.BloomIntensity = FMath::Lerp(0.675f, 16.0f, Alpha);
	Settings.AutoExposureBias = FMath::Lerp(0.0f, 10.0f, Alpha);
}

void ALobbyDoor::OnFinishedRectLight()
{
	RectLight->SetIntensity(0.f);

	PostProcess->BlendWeight = 0.f;

	FPostProcessSettings& Settings = PostProcess->Settings;
	Settings.BloomIntensity = 0.675f;
	Settings.AutoExposureBias = 0.f;
}

#pragma endregion