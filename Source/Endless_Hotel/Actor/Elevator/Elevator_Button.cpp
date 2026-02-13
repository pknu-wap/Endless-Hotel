// Copyright by 2025-2 WAP Game 2 team

#include "Actor/Elevator/Elevator_Button.h"
#include "Actor/Elevator/Elevator.h"
#include "Player/Controller/EHPlayerController.h"
#include "Component/Interact/InteractComponent.h"
#include <Components/WidgetComponent.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

AElevator_Button::AElevator_Button(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Pannel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_Mesh"));
	Pannel->SetupAttachment(RootComponent);

	Up_Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Up_Button"));
	Up_Button->SetupAttachment(Pannel);
	Up_ButtonRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Up_ButtonRing"));
	Up_ButtonRing->SetupAttachment(Pannel);
	Down_Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Down_Button"));
	Down_Button->SetupAttachment(Pannel);
	Down_ButtonRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Down_ButtonRing"));
	Down_ButtonRing->SetupAttachment(Pannel);

    Component_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Component Widget"));
    Component_Widget->SetupAttachment(Pannel);
    Component_Widget->SetWidgetSpace(EWidgetSpace::Screen);

    Component_Interact = CreateDefaultSubobject<UInteractComponent>(TEXT("Component_Interact"));
}

#pragma endregion

#pragma region Interact

void AElevator_Button::InteractElevator()
{
	if (OwnerElevator->bIsDoorMoving || OwnerElevator->bIsDoorOpened) return;
	
	MoveToButtonPlayer();
	FTimerHandle WaitOpen;
	GetWorld()->GetTimerManager().SetTimer(WaitOpen, FTimerDelegate::CreateWeakLambda(this, [this]() mutable
		{
			OwnerElevator->CallElevator();
		}), 1.0f, false);
}

void AElevator_Button::MoveToButtonPlayer()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player) return;

    FVector ButtonForward = GetActorForwardVector();

    FVector TargetLocation = GetActorLocation() + (ButtonForward * PlayerToElevatorDistance);

    TargetLocation.Z = Player->GetActorLocation().Z;

    FRotator TargetRotation = (-ButtonForward).Rotation();
    TargetRotation.Pitch = 0.0f;
    TargetRotation.Roll = 0.0f;

    UKismetSystemLibrary::MoveComponentTo(
        Player->GetRootComponent(),
        TargetLocation,
        TargetRotation,
        true,
        true,
        0.5f,
        false,
        EMoveComponentAction::Move,
        FLatentActionInfo(0, FMath::Rand(), TEXT("OnMoveCompleted"), this)
    );
}

void AElevator_Button::OnMoveCompleted()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player) return;

    if (AController* Controller = Player->GetController())
    {
        Controller->SetControlRotation(Player->GetActorRotation());

        if (AEHPlayerController* EHPC = Cast<AEHPlayerController>(Controller))
        {
            EHPC->OnEVButtonPressStarted();

            FTimerHandle ButtonAnim;
            GetWorld()->GetTimerManager().SetTimer(ButtonAnim, FTimerDelegate::CreateWeakLambda(this, [this, EHPC]()
                {
                    EHPC->OnEVButtonPressCompleted();
                }), 2.0f, false);
        }
    }
}
#pragma endregion