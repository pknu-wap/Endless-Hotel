#include "Actor/Elevator/Elevator_Button.h"
#include "Player/Controller/EHPlayerController.h"
#include "Component/Interact/InteractComponent.h"
#include <Components/WidgetComponent.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Components/AudioComponent.h>

#pragma region Base

AElevator_Button::AElevator_Button(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Pannel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_Mesh"));
    SetRootComponent(Pannel);

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

void AElevator_Button::BeginPlay()
{
    Super::BeginPlay();

    DownButtonDefaultLocation = Down_Button->GetRelativeLocation();
    DownButtonRingDefaultLocation = Down_ButtonRing->GetRelativeLocation();
}
#pragma endregion

#pragma region Interact

void AElevator_Button::InteractElevator()
{
    MoveToButtonPlayer();
}

void AElevator_Button::MoveToButtonPlayer()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player) return;

    AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
    PC->SetPlayerInputAble(false);
    PC->SetIgnoreLookInput(true);

    FVector ButtonLocation = GetActorLocation();
    FVector ButtonForward = GetActorForwardVector();
    FVector ButtonRight = GetActorRightVector();

    FVector TargetLocation = ButtonLocation
        + (ButtonForward * PlayerToElevatorDistance)
        + (ButtonRight * PlayerToElevatorSideOffset);
    TargetLocation.Z = Player->GetActorLocation().Z;

    FRotator TargetRotation = (-ButtonForward).Rotation();
    TargetRotation.Pitch = 0.0f;
    TargetRotation.Roll = 0.0f;

    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.ExecutionFunction = FName("OnMoveCompleted");
    LatentInfo.UUID = __LINE__;
    LatentInfo.Linkage = 0;

    UKismetSystemLibrary::MoveComponentTo(
        Player->GetRootComponent(),
        TargetLocation,
        TargetRotation,
        true, true, 0.5f, false,
        EMoveComponentAction::Move,
        LatentInfo
    );
}

void AElevator_Button::OnMoveCompleted()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player) return;

    AEHPlayerController* EHPC = Cast<AEHPlayerController>(Player->GetController());
    if (!EHPC) return;

    EHPC->SetControlRotation(Player->GetActorRotation());
    EHPC->OnEVButtonPressStarted();

    FTimerHandle PressAnimHandle;
    GetWorld()->GetTimerManager().SetTimer(PressAnimHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            PlayButtonPressAnimation();
            UGameplayStatics::PlaySoundAtLocation(
                this,
                ButtonPressSound,
                GetActorLocation()
            );
        }), ButtonTimerDuration, false);

    FTimerHandle ButtonAnimHandle;
    GetWorld()->GetTimerManager().SetTimer(ButtonAnimHandle, FTimerDelegate::CreateWeakLambda(this, [this, EHPC]()
        {
            if (OnButtonPressed.IsBound())
            {
                OnButtonPressed.Broadcast();
            }

            EHPC->OnEVButtonPressCompleted();
            EHPC->SetIgnoreLookInput(false);

        }), 2.0f, false);
}

#pragma endregion

#pragma region ButtonAnim

void AElevator_Button::PlayButtonPressAnimation()
{
    FVector PressedLocation_Button = DownButtonDefaultLocation;
    FVector PressedLocation_Ring = DownButtonRingDefaultLocation;

    PressedLocation_Button.X -= ButtonPressDistance;
    PressedLocation_Ring.X -= ButtonPressDistance;

    FLatentActionInfo LatentInfo1;
    LatentInfo1.CallbackTarget = this;
    LatentInfo1.ExecutionFunction = NAME_None;
    LatentInfo1.UUID = __LINE__;
    LatentInfo1.Linkage = 0;

    UKismetSystemLibrary::MoveComponentTo(
        Down_Button,
        PressedLocation_Button,
        Down_Button->GetRelativeRotation(),
        true,
        true,
        ButtonPressDuration,
        false,
        EMoveComponentAction::Move,
        LatentInfo1
    );

    FLatentActionInfo LatentInfo2;
    LatentInfo2.CallbackTarget = this;
    LatentInfo2.ExecutionFunction = FName("RestoreButtonPosition");
    LatentInfo2.UUID = __LINE__;
    LatentInfo2.Linkage = 0;

    UKismetSystemLibrary::MoveComponentTo(
        Down_ButtonRing,
        PressedLocation_Ring,
        Down_ButtonRing->GetRelativeRotation(),
        true,
        true,
        ButtonPressDuration,
        false,
        EMoveComponentAction::Move,
        LatentInfo2
    );
}

void AElevator_Button::RestoreButtonPosition()
{
    FLatentActionInfo LatentInfo1;
    LatentInfo1.CallbackTarget = this;
    LatentInfo1.ExecutionFunction = NAME_None;
    LatentInfo1.UUID = __LINE__;
    LatentInfo1.Linkage = 0;

    UKismetSystemLibrary::MoveComponentTo(
        Down_Button,
        DownButtonDefaultLocation,
        Down_Button->GetRelativeRotation(),
        true,
        true,
        ButtonPressDuration,
        false,
        EMoveComponentAction::Move,
        LatentInfo1
    );

    FLatentActionInfo LatentInfo2;
    LatentInfo2.CallbackTarget = this;
    LatentInfo2.ExecutionFunction = NAME_None;
    LatentInfo2.UUID = __LINE__;
    LatentInfo2.Linkage = 0;

    UKismetSystemLibrary::MoveComponentTo(
        Down_ButtonRing,
        DownButtonRingDefaultLocation,
        Down_ButtonRing->GetRelativeRotation(),
        true,
        true,
        ButtonPressDuration,
        false,
        EMoveComponentAction::Move,
        LatentInfo2
    );
}

#pragma endregion