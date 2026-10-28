// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Bed/Bed.h"
#include "GameSystem/SubSystem/EHGameSystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "Player/Character/EHPlayer.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

ABed::ABed(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Direction = CreateDefaultSubobject<UBedDirectionComponent>(TEXT("Comp_Direction"));
}

void ABed::BeginPlay()
{
	Super::BeginPlay();

	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	GameSystem->OnProgressionChanged.AddUObject(this, &ThisClass::OnChangedProgression);

	bool bActive = GameSystem->GetGameProgression() == EGameProgression::CheckIn;
	Component_Interact->ActiveInteract(bActive);

	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->OnRevive.AddUObject(this, &ThisClass::StartWakeUp);

	auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	if (GameSystem->GetGameProgression() != EGameProgression::CheckIn && FloorSub->GetIsFirstFloor())
	{
		StartWakeUp();
	}
}

void ABed::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	if (IsValid(GameSystem))
	{
		GameSystem->OnProgressionChanged.RemoveAll(this);
	}

	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnRevive.RemoveAll(this);
	}

	Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Interact

void ABed::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();
	switch (Info.InteractType)
	{
	case EInteractType::Rest:
		StartRest();
		break;
	}
}

#pragma endregion

#pragma region Progression

void ABed::OnChangedProgression(EGameProgression Target)
{
	bool bActive = Target == EGameProgression::CheckIn;
	Component_Interact->ActiveInteract(bActive);
}

#pragma endregion

#pragma region Rest

void ABed::StartRest()
{
	Comp_Direction->SetPlayerInputAble(false);
	Comp_Direction->ShowDirection(RestInfo);

	FBedDirectionInfo LastInfo = RestInfo.Top();
	FTimerHandle EyeHandle;
	GetWorld()->GetTimerManager().SetTimer(EyeHandle, FTimerDelegate::CreateUObject(Comp_Direction, &UBedDirectionComponent::ShowEyeEffect, false), LastInfo.Delay + LastInfo.Duration, false);

	constexpr float WakeUpDelay = 8.f;
	FTimerHandle WakeUpHandle;
	GetWorld()->GetTimerManager().SetTimer(WakeUpHandle, FTimerDelegate::CreateUObject(this, &ThisClass::StartWakeUp), LastInfo.Delay + LastInfo.Duration + WakeUpDelay, false);
}

void ABed::StartWakeUp()
{
	auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player->SetActorTransform(WakeInfo[0].TargetTrans);
	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetControlRotation(WakeInfo[0].TargetTrans.Rotator());

	Comp_Direction->SetPlayerInputAble(false);
	Comp_Direction->ShowEyeEffect(true);

	constexpr float StartDelay = 6.f;
	FTimerHandle StartHandle;
	GetWorld()->GetTimerManager().SetTimer(StartHandle, FTimerDelegate::CreateUObject(Comp_Direction, &UBedDirectionComponent::ShowDirection, WakeInfo), StartDelay, false);

	FBedDirectionInfo LastInfo = WakeInfo.Top();
	constexpr float InputDelay = 6.f;
	FTimerHandle InputHandle;
	GetWorld()->GetTimerManager().SetTimer(InputHandle, FTimerDelegate::CreateUObject(Comp_Direction, &UBedDirectionComponent::SetPlayerInputAble, true), LastInfo.Delay + LastInfo.Duration + InputDelay, false);

	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	if (GameSystem->GetGameProgression() == EGameProgression::CheckIn)
	{
		GameSystem->ChangeProgression(EGameProgression::Tutorial);
	}
}

#pragma endregion