// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Door/LobbyDoor.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Character/EHPlayer.h"
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SpotLightComponent.h>
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

	AC_SpotLight = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_SpotLight"));
	AC_SpotLight->SetupAttachment(SpotLight);
	AC_SpotLight->SetAutoActivate(false);

	Object->SetupAttachment(RootComponent);
}

void ALobbyDoor::BeginPlay()
{
	Super::BeginPlay();

	LeftCloseRot = DoorLeft->GetRelativeRotation();
	RightCloseRot = DoorRight->GetRelativeRotation();

	bool bActive = USaveManager::LoadData_Progression().Progression != EGameProgression::CheckIn;
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
	AC_SpotLight->Play();
}

#pragma endregion