// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Shrink/Anomaly_Shrink.h"
#include "Player/Controller/EHPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/TimelineComponent.h>

#pragma region Base

AAnomaly_Shrink::AAnomaly_Shrink(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Timeline_Shrink = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Shrink"));
}

void AAnomaly_Shrink::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat Update_Size;
	Update_Size.BindUFunction(this, FName("ShrinkPlayer"));
	Timeline_Shrink->AddInterpFloat(Curve_Shrink, Update_Size);

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerSM = Player->GetMesh();
	PlayerMC = Player->GetCharacterMovement();
	OriginalScale = PlayerSM->GetRelativeScale3D();
	OriginalSpeed = PlayerMC->MaxWalkSpeed;
}

#pragma endregion

#pragma region Activity

void AAnomaly_Shrink::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Shrink:
		AnomalyAction = ([this](AAnomaly_Object_Base* Object)
			{
				Timeline_Shrink->PlayFromStart();
			});
		ScheduleAnomaly(5);
		break;
	}
}

#pragma endregion

#pragma region Shrink

void AAnomaly_Shrink::ShrinkPlayer(float Value)
{
	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->bCanRun = false;
	PC->bCanCrouch = false;

	PlayerSM->SetRelativeScale3D(OriginalScale * Value);
	PlayerMC->MaxWalkSpeed = OriginalSpeed * Value;
}

#pragma endregion