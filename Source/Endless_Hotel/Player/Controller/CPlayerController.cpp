// Copyright by 2025-2 WAP Game 2 team


#include "Player/Controller/CPlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

ACPlayerController::ACPlayerController()
{

}

void ACPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Enhanced Input 서브시스템에 매핑 컨텍스트 추가
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (InputMappingContext)
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
            UE_LOG(LogTemp, Warning, TEXT("Input Mapping Context Added!"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Input Mapping Context is NULL!"));
        }
    }
}

void ACPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // Move Actions
        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ACPlayerController::MoveForward);
        EnhancedInputComponent->BindAction(IA_MoveRight, ETriggerEvent::Triggered, this, &ACPlayerController::MoveRight);

        // Look Actions
        EnhancedInputComponent->BindAction(IA_LookForward, ETriggerEvent::Triggered, this, &ACPlayerController::LookForward);
        EnhancedInputComponent->BindAction(IA_LookRight, ETriggerEvent::Triggered, this, &ACPlayerController::LookRight);
    }
}

void ACPlayerController::MoveForward(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();

    if (ACharacter* ControlledCharacter = GetCharacter())
    {
        if (ScaleValue != 0.0f)
        {
            const FRotator CurrentRotation = GetControlRotation();
            const FRotator YawRotation(0.0f, CurrentRotation.Yaw, 0.0f);
            const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
            ControlledCharacter->AddMovementInput(ForwardDirection, ScaleValue);
        }
    }
}

void ACPlayerController::MoveRight(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();

    if (ACharacter* ControlledCharacter = GetCharacter())
    {
        if (ScaleValue != 0.0f)
        {
            const FRotator CurrentRotation = GetControlRotation();
            const FRotator YawRotation(0.0f, CurrentRotation.Yaw, 0.0f);
            const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
            ControlledCharacter->AddMovementInput(RightDirection, ScaleValue);
        }
    }
}

void ACPlayerController::LookForward(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();

    if (UCameraComponent* CameraComponent = GetPlayerCamera())
    {
        FRotator CurrentRotation = CameraComponent->GetRelativeRotation();
        float NewPitch = CurrentRotation.Pitch + (ScaleValue * LookSensitivity);
        NewPitch = FMath::Clamp(NewPitch, -45.0f, 0.0f);

        FRotator NewRotation = FRotator(NewPitch, CurrentRotation.Yaw, CurrentRotation.Roll);
        CameraComponent->SetRelativeRotation(NewRotation);
    }
}

void ACPlayerController::LookRight(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();
    AddYawInput(ScaleValue * LookSensitivity);
}

UCameraComponent* ACPlayerController::GetPlayerCamera() const
{
    if (ACharacter* ControlledCharacter = GetCharacter())
    {
        return ControlledCharacter->FindComponentByClass<UCameraComponent>();
    }
    return nullptr;
}