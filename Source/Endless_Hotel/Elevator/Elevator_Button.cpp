// Copyright by 2025-2 WAP Game 2 team

#include "Elevator/Elevator_Button.h"
#include "Elevator/Elevator.h"
#include "Component/LookAt/LookAtComponent.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Player/Controller/EHPlayerController.h"
#include <Components/WidgetComponent.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>

#define LOCTEXT_NAMESPACE "Elevator"

#pragma region Base

AElevator_Button::AElevator_Button(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Pannel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_Mesh"));
	Pannel->SetupAttachment(RootComponent);
	Pannel->SetRelativeLocation(FVector3d(40.f, 47.f, -19.f));

	Up_Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Up_Button"));
	Up_Button->SetupAttachment(Pannel);
	Up_ButtonRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Up_ButtonRing"));
	Up_ButtonRing->SetupAttachment(Pannel);
	Down_Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Down_Button"));
	Down_Button->SetupAttachment(Pannel);
	Down_ButtonRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Down_ButtonRing"));
	Down_ButtonRing->SetupAttachment(Pannel);

	WC = CreateDefaultSubobject<UWidgetComponent>(TEXT("WC"));
	WC->SetupAttachment(Pannel);

	LAC = CreateDefaultSubobject<ULookAtComponent>(TEXT("LAC"));
}

void AElevator_Button::BeginPlay()
{
	Super::BeginPlay();

	UI_Interact = Cast<UUI_Interact>(WC->GetUserWidgetObject());
	UI_Interact->SetDescription(LOCTEXT("Key1", "버튼 누르기"));

	LAC->SettingWidgetComponent(WC);
}

#pragma endregion

#pragma region Interact

void AElevator_Button::Interacted_Implementation()
{
	if (OwnerElevator->bIsDoorMoving || OwnerElevator->bIsDoorOpened) return;
	
	MoveToButtonPlayer();
	OwnerElevator->CallElevator();
	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateWeakLambda(this, [this]() mutable
		{
			OwnerElevator->TryCloseDoorAfterDelay();
		}), 4.0f, false);
}

void AElevator_Button::ShowInteractWidget_Implementation(bool bIsShow)
{
	UI_Interact->ShowDescription(bIsShow);
}

void AElevator_Button::MoveToButtonPlayer()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector3d FixedLocation = Player->GetActorLocation();


	FixedLocation.X = PlayerLocationButton.X;
	FixedLocation.Y = PlayerLocationButton.Y;
	Player->SetActorLocation(FixedLocation);

	if (AController* Controller = Player->GetController())
	{
		if (AEHPlayerController* EHPC = Cast<AEHPlayerController>(Controller))
		{
			EHPC->SetControlRotation(PlayerRotationButton);
			EHPC->OnButtonPressStarted();
			FTimerHandle ButtonAnim;
			GetWorld()->GetTimerManager().SetTimer(ButtonAnim, FTimerDelegate::CreateWeakLambda(this, [this, EHPC]() mutable
				{
					EHPC->OnButtonPressCompleted();
				}), 2.0f, false);
		}
	}
}
#pragma endregion

#undef LOCTEXT_NAMESPACE