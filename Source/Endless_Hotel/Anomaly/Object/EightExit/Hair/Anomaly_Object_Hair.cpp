// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Hair/Anomaly_Object_Hair.h"
#include "Player/Character/EHPlayer.h"
#include <Components/AudioComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

AAnomaly_Object_Hair::AAnomaly_Object_Hair(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SK_Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_Hair"));
	SetRootComponent(SK_Hair);

	Object->SetupAttachment(RootComponent);

	AC_Hair = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Hair"));
	AC_Hair->SetupAttachment(RootComponent);
	AC_Hair->SetAutoActivate(false);
}

void AAnomaly_Object_Hair::BeginPlay()
{
	Super::BeginPlay();

	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Camera = Player->GetCamera();

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	SlowDownHair();
}

void AAnomaly_Object_Hair::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector CameraForward = PC->GetControlRotation().Vector();
	FVector TargetDir = (Object->GetComponentLocation() - Camera->GetComponentLocation()).GetSafeNormal();
	const float Dot = FVector::DotProduct(CameraForward, TargetDir);

	if (Dot >= 0.7f && !bPlayAudio)
	{
		bPlayAudio = true;
		AC_Hair->Play();
	}
}

#pragma endregion

#pragma region Hair

void AAnomaly_Object_Hair::SlowDownHair()
{
	OriginLoc = SK_Hair->GetRelativeLocation();
	TargetLoc = OriginLoc;
	TargetLoc.X -= 60.f;

	GetWorld()->GetTimerManager().SetTimer(MoveHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			FVector CurrentLoc = SK_Hair->GetRelativeLocation();
			FVector MoveLoc = FMath::VInterpTo(CurrentLoc, TargetLoc, GetWorld()->GetDeltaSeconds(), 5.f);
			SK_Hair->SetRelativeLocation(MoveLoc);

			if (MoveLoc.Equals(TargetLoc))
			{
				SK_Hair->SetRelativeLocation(TargetLoc);
				GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
			}
		}), 0.1f, true);
}

#pragma endregion