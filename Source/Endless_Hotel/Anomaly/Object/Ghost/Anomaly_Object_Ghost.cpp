// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Ghost/Anomaly_Object_Ghost.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Player/Controller/EHPlayerController.h"
#include "TimerManager.h"

#pragma region Base

AAnomaly_Object_Ghost::AAnomaly_Object_Ghost(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);

    StepIndex = 0;
    bHasTriggered = false;
}

#pragma endregion

#pragma region GhostReveal

void AAnomaly_Object_Ghost::BeginPlay()
{
    Super::BeginPlay();

    // 게임 시작 시에는 절대 보이면 안 됨
    SetActorHiddenInGame(true);
    Mesh->SetVisibility(false, true);
}


void AAnomaly_Object_Ghost::StartGhostSequence()
{
    Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!Player || !PC) return;

    SpawnLocation = FVector(-2890.0, 570.f, 600.f);

    SetActorLocation(SpawnLocation);

    StepIndex = 0;
    StartStep();
}



void AAnomaly_Object_Ghost::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bTriggerEnabled) { 
        if (bHasTriggered) return;

        if (!Player)
            Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

        FVector P = Player->GetActorLocation();

        if (P.X < -1300.f)
        {   
            Reveal();
            if (P.X < -1600.f) {
                bHasTriggered = true;
                StartGhostSequence();
            }
        }
    }
}
void AAnomaly_Object_Ghost::Reveal() {
    SetActorHiddenInGame(false);
    Mesh->SetVisibility(true, true);
}

void AAnomaly_Object_Ghost::StartStep()
{
     
    if (StepIndex >= 3)
    {
        FinishSequence();
        return;
    }

    // 화면 어둡게
    FadeScreen(true);

    // 0.3초 후 이동
    FTimerHandle TH;
    GetWorld()->GetTimerManager().SetTimer(
        TH, this, &AAnomaly_Object_Ghost::MoveStep,
        0.3f, false
    );
}

void AAnomaly_Object_Ghost::MoveStep()
{
    FVector PlayerLoc = Player->GetActorLocation();
    FVector Forward = Player->GetActorForwardVector();

    // 마지막 Step이면 플레이어 앞 100cm로 이동
    if (StepIndex == 2)  // 0,1,2 → 3단계
    {   
        AEHPlayerController* EHPC = Cast<AEHPlayerController>(PC);
        EHPC->bCanMove = false;
        EHPC->bIsCameraFixed = true;

        FVector NearLoc = PlayerLoc + Forward * 50.f;
        NearLoc.Z = SpawnLocation.Z;

        FRotator GhostLookRot = (PlayerLoc - NearLoc).Rotation();
        GhostLookRot.Pitch = 0.f;
        GhostLookRot.Roll = 0.f;

        UCameraComponent* Cam = Player->FindComponentByClass<UCameraComponent>();
        Cam->SetRelativeRotation(FRotator(20.f, 0.f, 0.f));

        SetActorRotation(GhostLookRot);

        SetActorLocation(NearLoc);

        FadeScreen(false);
        StepIndex++;

        // 바로 FinishSequence() 호출
        FTimerHandle TH;
        GetWorld()->GetTimerManager().SetTimer(
            TH, this, &AAnomaly_Object_Ghost::FinishSequence,
            1.0f, false
        );

        FTimerHandle MoveRestoreHandle;
        GetWorld()->GetTimerManager().SetTimer(
            MoveRestoreHandle,
            [EHPC]()
            {
                 EHPC->bCanMove = true;
                 EHPC->bIsCameraFixed = false;
            },
            4.0f,
            false
        );
        return;
    }

    float Ratio = (StepIndex + 1) / 3.0f;
    FVector NewLoc = FMath::Lerp(SpawnLocation, PlayerLoc, Ratio);
    NewLoc.Z = SpawnLocation.Z;

    SetActorLocation(NewLoc);
    FadeScreen(false);

    StepIndex++;

    FTimerHandle TH;
    GetWorld()->GetTimerManager().SetTimer(
        TH, this, &AAnomaly_Object_Ghost::StartStep,
        1.0f, false
    );
}
 
#pragma endregion

#pragma region CameraMoving

void AAnomaly_Object_Ghost::FinishSequence()
{
    FVector P = Player->GetActorLocation();
    FVector Forward = Player->GetActorForwardVector();

    FVector FinalLoc = P + Forward * 50.f;
    FinalLoc.Z = SpawnLocation.Z;

    SetActorLocation(FinalLoc);

    FadeScreen(false);
    if (PC && CameraShakeClass)
    {
        PC->PlayerCameraManager->StartCameraShake(CameraShakeClass, 3.0f);
    }

    SetLifeSpan(3.f);

}

#pragma endregion

#pragma region Fade

void AAnomaly_Object_Ghost::FadeScreen(bool bFadeOut)
{
    if (!PC) return;

    float From = bFadeOut ? 0.f : 1.f;
    float To = bFadeOut ? 1.f : 0.f;

    PC->PlayerCameraManager->StartCameraFade(
        From, To,
        0.25f,
        FLinearColor::Black,
        false,
        true
    );
}

#pragma endregion