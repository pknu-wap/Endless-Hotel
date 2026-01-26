// Copyright by 2025-2 WAP Game 2 team

#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Component/EHCameraComponent.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

#pragma region Base

AEHPlayer::AEHPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Component_Camera = CreateDefaultSubobject<UEHCameraComponent>(TEXT("Component_Camera"));

	DieDelegate.AddDynamic(this, &ThisClass::DiePlayer);
}


void AEHPlayer::BeginPlay()
{
	Super::BeginPlay();
		// 클래스 내에 이미 선언된 Third 변수가 있다면 할당
		if (!Third_Mesh)
		{
			// 블루프린트에 추가된 "Third"라는 이름의 컴포넌트를 찾아옵니다.
			Third_Mesh = Cast<USkeletalMeshComponent>(GetDefaultSubobjectByName(TEXT("Third")));
		}
}
#pragma endregion

#pragma region Death

void AEHPlayer::DiePlayer(const EDeathReason& DeathReason)
{
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
			auto* SubSystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
			SubSystem->ApplyVerdict();
		}), AnimLength + 5, false);
}

void AEHPlayer::FreezeAnimation()
{
	if (GetMesh())
	{
		// 애니메이션 포즈를 현재 상태로 고정하고 업데이트 중단
		GetMesh()->bNoSkeletonUpdate = true;
	}
	if (Third_Mesh)
	{
		Third_Mesh->bNoSkeletonUpdate = true;
	}
}

#pragma endregion