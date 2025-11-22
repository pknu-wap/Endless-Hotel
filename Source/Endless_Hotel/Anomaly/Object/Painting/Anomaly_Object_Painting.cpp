// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Niagara/Public/NiagaraComponent.h"

#pragma region Base

AAnomaly_Object_Painting::AAnomaly_Object_Painting(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_Painting = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Painting"));
	SetRootComponent(Mesh_Painting);

	Mesh_LeftEye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_LeftEye"));
	Mesh_LeftEye->SetupAttachment(RootComponent);
	Mesh_LeftEye->SetRelativeLocation(FVector(2, -12, 23));
	Mesh_LeftEye->SetRelativeRotation(FRotator(0, 0, -90));

	Mesh_RightEye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_RightEye"));
	Mesh_RightEye->SetupAttachment(RootComponent);
	Mesh_RightEye->SetRelativeLocation(FVector(2, 3, 23));
	Mesh_RightEye->SetRelativeRotation(FRotator(0, 0, -90));

	Niagara_Blood_Left = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Blood_Left"));
	Niagara_Blood_Left->SetupAttachment(RootComponent);
	Niagara_Blood_Left->SetAutoActivate(false);

	Niagara_Blood_Right = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Blood_Right"));
	Niagara_Blood_Right->SetupAttachment(RootComponent);
	Niagara_Blood_Right->SetAutoActivate(false);
}

#pragma endregion

#pragma region EyeMove

void AAnomaly_Object_Painting::EyeFollowing()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FTimerHandle EyeFollowHandle;
	FTimerDelegate EyeFollowDelegate = FTimerDelegate::CreateWeakLambda(
		this,
		[this, Player]()
		{
			const FTransform SelfXform = GetActorTransform();
			FVector PlayerLocal = SelfXform.InverseTransformPosition(Player->GetActorLocation());

			const float lateralY = PlayerLocal.Y;

			constexpr float DeadZoneCm = 2.f;
			constexpr float Sensitivity = 250.f;
			constexpr float YawLimitDeg = 45.f;

			float targetYaw = 0.f;
			if (FMath::Abs(lateralY) > DeadZoneCm)
			{
				targetYaw = FMath::RadiansToDegrees(FMath::Atan2(lateralY, Sensitivity));
				targetYaw = FMath::Clamp(targetYaw, -45.f, 45.f);
			}

			const FRotator EyeRot(0.f, targetYaw - 90, 0.f);
			Mesh_LeftEye->SetRelativeRotation(EyeRot);
			Mesh_RightEye->SetRelativeRotation(EyeRot);
		});
	GetWorld()->GetTimerManager().SetTimer(EyeFollowHandle, EyeFollowDelegate, 0.17f, true);
}

#pragma endregion

#pragma region Blood

void AAnomaly_Object_Painting::BloodDropping()
{
	TWeakObjectPtr<AAnomaly_Object_Painting> Wrapper = this;
	FTimerHandle BloodHandle;
	GetWorld()->GetTimerManager().SetTimer(BloodHandle, [Wrapper]()
		{
			Wrapper->Niagara_Blood_Left->SetActive(true);
			Wrapper->Niagara_Blood_Right->SetActive(true);
		}, 15, false);
}

#pragma endregion