// Copyright by 2025-2 WAP Game 2 team


#include "Player/CPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

ACPlayer::ACPlayer()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ACPlayer::BeginPlay()
{
    Super::BeginPlay();

    // Enhanced Input 서브시스템에 매핑 컨텍스트 추가
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Move Actions
        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ACPlayer::MoveForward);
        EnhancedInputComponent->BindAction(IA_MoveRight, ETriggerEvent::Triggered, this, &ACPlayer::MoveRight);

        // Look Actions
        EnhancedInputComponent->BindAction(IA_LookForward, ETriggerEvent::Triggered, this, &ACPlayer::LookForward);
        EnhancedInputComponent->BindAction(IA_LookRight, ETriggerEvent::Triggered, this, &ACPlayer::LookRight);
    }
}

void ACPlayer::MoveForward(const FInputActionValue& Value)
{
    // Action Value 가져오기 (Scale Value)
    const float ScaleValue = Value.Get<float>();

    if (Controller && ScaleValue != 0.0f)
    {
        // 컨트롤러의 회전값 가져오기
        const FRotator ControlRotation = GetControlRotation();
        const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);

        // Forward 벡터 계산
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // World Direction으로 이동 입력 추가
        AddMovementInput(ForwardDirection, ScaleValue);
    }
}

void ACPlayer::MoveRight(const FInputActionValue& Value)
{
    // Action Value 가져오기 (Scale Value)
    const float ScaleValue = Value.Get<float>();

    if (Controller && ScaleValue != 0.0f)
    {
        // 컨트롤러의 회전값 가져오기
        const FRotator ControlRotation = GetControlRotation();
        const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);

        // Right 벡터 계산
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // World Direction으로 이동 입력 추가
        AddMovementInput(RightDirection, ScaleValue);
    }
}


void ACPlayer::LookForward(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();

    if (Controller)
    {
        UCameraComponent* CameraComponent = FindComponentByClass<UCameraComponent>();

        if (CameraComponent)
        {
            FRotator CurrentRotation = CameraComponent->GetRelativeRotation();

            // 마우스 입력을 직접 Pitch에 더함 (민감도 적용)
            float NewPitch = CurrentRotation.Pitch + (ScaleValue * 1.0f);

            // -45.0 ~ 0.0 범위로 제한
            NewPitch = FMath::Clamp(NewPitch, -79.0f, 79.0f);

            FRotator NewRotation = FRotator(NewPitch, CurrentRotation.Yaw, CurrentRotation.Roll);
            CameraComponent->SetRelativeRotation(NewRotation);
        }
    }
}

void ACPlayer::LookRight(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();

    if (Controller)
    {
        // 민감도를 적용한 회전 입력
        AddControllerYawInput(ScaleValue * 1.0f);
    }
}