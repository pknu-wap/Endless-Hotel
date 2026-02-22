// Copyright by 2025-2 WAP Game 2 team

#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Component/EHCameraComponent.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>

#pragma region Base

AEHPlayer::AEHPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Component_Camera = CreateDefaultSubobject<UEHCameraComponent>(TEXT("Component_Camera"));

	Third_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Third_Mesh"));
	Third_Mesh->SetupAttachment(GetMesh());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Third_Mesh, TEXT("HeadSocket"));
	SpringArm->TargetArmLength = 20.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	DieDelegate.AddDynamic(this, &ThisClass::DiePlayer);

}


void AEHPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (!Third_Mesh)
	{
		Third_Mesh = Cast<USkeletalMeshComponent>(GetDefaultSubobjectByName(TEXT("Third")));
	}
}
#pragma endregion

#pragma region Death

void AEHPlayer::DiePlayer(const EDeathReason& DeathReason)
{
	bIsDead = true;
 	UAnimMontage* DeathAnim = DeathAnims[DeathReason];

	AEHPlayerController* PC = Cast<AEHPlayerController>(GetController());
	if (PC)
	{
		PC->PlayDeathSequence();
	}

	PlayAnimMontage(DeathAnim);

	UAnimInstance* ThirdAnimInst = Third_Mesh->GetAnimInstance();
	if (ThirdAnimInst)
	{
		ThirdAnimInst->Montage_Play(DeathAnim);
	}

	const float AnimLength = DeathAnim->GetPlayLength();

	const float FreezeTime = FMath::Max(0.0f, AnimLength - 0.15f);

	FTimerHandle FreezeHandle;
	GetWorld()->GetTimerManager().SetTimer(FreezeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			FreezeAnimation();
		}), FreezeTime, false);

	FTimerHandle EyeHandle;
	GetWorld()->GetTimerManager().SetTimer(EyeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Component_Camera->StartEyeEffect(false);
		}), AnimLength, false);

	FTimerHandle DeathHandle;
	GetWorld()->GetTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* SubSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
			SubSystem->ApplyVerdict();
		}), AnimLength + 5, false);
}

void AEHPlayer::FreezeAnimation()
{
	if (GetMesh())
	{
		GetMesh()->bNoSkeletonUpdate = true;
	}
	if (Third_Mesh)
	{
		Third_Mesh->bNoSkeletonUpdate = true;
	}
}

#pragma endregion