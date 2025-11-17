// Copyright by 2025-2 WAP Game 2 team

#include "Player/Controller/EHPlayerController.h"
#include "UI/Controller/UI_Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Interact/Interact_Base.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

#pragma region Base

AEHPlayerController::AEHPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

    //Interact
    bCanInteract = false;
    TraceDistance = 300.f;
    CurrentInteractActor = nullptr;
    PrimaryActorTick.bCanEverTick = true;
}



void AEHPlayerController::BeginPlay()
{
	Super::BeginPlay();

    APawn* ControlledPawn = GetPawn();

    if (ControlledPawn)
    {
        UCameraComponent* PlayerCamera = ControlledPawn->FindComponentByClass<UCameraComponent>();
        if (PlayerCamera)
        {
            UE_LOG(LogTemp, Warning, TEXT("Camera Founded!: %s"), *PlayerCamera->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("No Camera Component on Pawn!"));
        }
    }

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Default, 0);
	}

}

#pragma endregion

#pragma region Input

void AEHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Move Actions
		EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ThisClass::MoveForward);
		EnhancedInputComponent->BindAction(IA_MoveRight, ETriggerEvent::Triggered, this, &ThisClass::MoveRight);

		// Look Actions
		EnhancedInputComponent->BindAction(IA_LookForward, ETriggerEvent::Triggered, this, &ThisClass::LookForward);
		EnhancedInputComponent->BindAction(IA_LookRight, ETriggerEvent::Triggered, this, &ThisClass::LookRight);

		//ESC
		EnhancedInputComponent->BindAction(IA_ESC, ETriggerEvent::Started, this, &ThisClass::EscapeStarted);

		//Run
		EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Triggered, this, &ThisClass::OnRunTriggered);
        EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Completed, this, &ThisClass::OnRunCompleted);

		//InterAct
		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &ThisClass::OnInteract);

		//Crouch
        EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &AEHPlayerController::Crouch_Triggered);
        EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AEHPlayerController::Crouch_Completed);

        //FaceCover
        EnhancedInputComponent->BindAction(IA_FaceCover, ETriggerEvent::Triggered, this, &AEHPlayerController::FaceCover_Triggered);
	}
}

void AEHPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    CheckForInteractables();
}

void AEHPlayerController::CheckForInteractables()
{
    if (!GetPlayerCamera()) return;

    FVector Start = GetPlayerCamera()->GetComponentLocation();
    FVector End = Start + GetPlayerCamera()->GetForwardVector() * TraceDistance;

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetPawn());

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility,
        Params
    );

    // Debug line (시각 확인용)
    // DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.0f, 0, 1.0f);

    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();

        if (HitActor && HitActor->IsA(AInteract_Base::StaticClass()))
        {
            bCanInteract = true;
            CurrentInteractActor = HitActor;
            return;
        }
    }

    // 트레이스 실패 or 유효하지 않음
    bCanInteract = false;
    CurrentInteractActor = nullptr;
}


void AEHPlayerController::OnInteract(const FInputActionValue& Value)
{
    if (!bCanInteract || !GetPlayerCamera()) return;

    // 혹은 인터랙터에게 특정 함수 호출
    if (CurrentInteractActor)
    {
        // 예시: 인터랙터의 함수 호출
        if (AInteract_Base* Interactable = Cast<AInteract_Base>(CurrentInteractActor))
        {
            Interactable->Interact(this);
        }
    }
}



void AEHPlayerController::EscapeStarted(const FInputActionValue& InputValue)
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();

	if (UICon->GetCurrentPopUpWidget())
	{
		UICon->ClosePopUpWidget(true);
		return;
	}

	UICon->OpenPopUpWidget(UI_Escape);
}

void AEHPlayerController::MoveForward(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();

    if (ACharacter* ControlledCharacter = GetCharacter())
    {
        if (bCanMove) {
            if (ScaleValue != 0.0f)
            {
                const FRotator CurrentRotation = GetControlRotation();
                const FRotator YawRotation(0.0f, CurrentRotation.Yaw, 0.0f);
                const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
                ControlledCharacter->AddMovementInput(ForwardDirection, ScaleValue);
            }
        }
    }
}

void AEHPlayerController::MoveRight(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();

    if (ACharacter* ControlledCharacter = GetCharacter())
    {   
        if (bCanMove) {
            if (ScaleValue != 0.0f)
            {
                const FRotator CurrentRotation = GetControlRotation();
                const FRotator YawRotation(0.0f, CurrentRotation.Yaw, 0.0f);
                const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
                ControlledCharacter->AddMovementInput(RightDirection, ScaleValue);
            }
        }
    }
}

void AEHPlayerController::LookForward(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();

    if (!bIsCameraFixed) {
        if (UCameraComponent* CameraComponent = GetPlayerCamera())
        {
            FRotator CurrentRotation = CameraComponent->GetRelativeRotation();
            float NewPitch = CurrentRotation.Pitch + (ScaleValue * LookSensitivity);
            NewPitch = FMath::Clamp(NewPitch, -45.0f, 0.0f);

            FRotator NewRotation = FRotator(NewPitch, CurrentRotation.Yaw, CurrentRotation.Roll);
            CameraComponent->SetRelativeRotation(NewRotation);
        }
    }
}

void AEHPlayerController::LookRight(const FInputActionValue& Value)
{
    const float ScaleValue = Value.Get<float>();
    AddYawInput(ScaleValue * LookSensitivity);
}

//Run
void AEHPlayerController::OnRunTriggered()
{
    bIsRunning = true;

    if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
    {
        ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
    }
}

void AEHPlayerController::OnRunCompleted()
{
    bIsRunning = false;

    if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
    {
        ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}

void AEHPlayerController::Crouch_Triggered()
{
    if (bIsCrouching)
        return;

    bIsCrouching = true;

    GetCharacter()->Crouch();
    GetCharacter()->GetCapsuleComponent()->SetCapsuleSize(45.f, 63.f);

    //SpringArm 카메라 위치 아래로 이동
    if (SpringArm)
        SpringArm->AddRelativeLocation(FVector(0.f, 0.f, -50.f));
}
void AEHPlayerController::Crouch_Completed()
{
    if (!bIsCrouching)
        return;

    bIsCrouching = false;

    GetCharacter()->UnCrouch();
    GetCharacter()->GetCapsuleComponent()->SetCapsuleSize(45.f, 100.f);

    //SpringArm 카메라 위치 위로 이동
    if (SpringArm)
        SpringArm->AddRelativeLocation(FVector(0.f, 0.f, 50.f));
}


//FaceCover
void AEHPlayerController::FaceCover_Triggered()
{   
    ACharacter* ControlledCharacter = Cast<ACharacter>(GetCharacter());
    FVector fVelocity = ControlledCharacter->GetVelocity();
    float Speed = fVelocity.Size();

    if (Speed > 0.0f)
        return; // 이동 중이면 전환 금지

    // 상태 토글
    bIsFaceCovering = !bIsFaceCovering;
    bIsCameraFixed = !bIsCameraFixed;
    bCanMove = !bCanMove;

    // SpringArm & Camera 가져오기
    if (!SpringArm)
    {
        SpringArm = ControlledCharacter->FindComponentByClass<USpringArmComponent>();
    }

    if (!PlayerCameraComponent)
    {
        PlayerCameraComponent = ControlledCharacter->FindComponentByClass<UCameraComponent>();
    }

    if (!SpringArm || !PlayerCameraComponent)
        return;

    // 카메라 전환 로직
    if (bIsFaceCovering)
    {
        // 얼굴 보기 모드로 전환
        SpringArm->AddRelativeLocation(FVector(-3.4f, -10.5f, 0.f));
        PlayerCameraComponent->SetRelativeRotation(FRotator(0.f, -20.f, 0.f));
    }
    else
    {
        // 원래 위치로 복귀
        SpringArm->AddRelativeLocation(FVector(3.4, 10.5f, 0.f));
    }
}



UCameraComponent* AEHPlayerController::GetPlayerCamera() const
{
    if (ACharacter* ControlledCharacter = GetCharacter())
    {
        return ControlledCharacter->FindComponentByClass<UCameraComponent>();
    }
    return nullptr;
}
#pragma endregion