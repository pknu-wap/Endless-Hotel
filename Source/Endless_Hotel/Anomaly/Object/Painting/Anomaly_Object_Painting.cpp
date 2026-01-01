// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"
#include "UI/PopUp/Default/PaintingBlur/UI_PopUp_PaintingBlur.h"
#include "UI/Base/InGame/Interact/UI_Interact.h"
#include "Component/LookAt/LookAtComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>
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

	Widget_PaintingBlur = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget_PaintingBlur"));
	Widget_PaintingBlur->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->InitBoxExtent(FVector(100, 100, 100));
	TriggerBox->SetRelativeLocation(FVector(100, -100, -40));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bSolved = false;
}

#pragma endregion

#pragma region Trigger

void AAnomaly_Object_Painting::ActiveTrigger()
{
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnTriggerBeginOverlap);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBeginOverlap);
}

void AAnomaly_Object_Painting::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	switch (CurrentAnomalyID)
	{
	case 24:
		EyeFollowing();
		break;
	case 27:
		BloodDropping();
		break;
	case 31:
		BlurPaint();
		break;
	default:
		break;
	}
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion

#pragma region EyeMove

void AAnomaly_Object_Painting::EyeFollowing()
{
	Mesh_LeftEye->SetVisibleFlag(true);
	Mesh_RightEye->SetVisibleFlag(true);
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FTimerHandle EyeFollowHandle;
	GetWorld()->GetTimerManager().SetTimer(EyeFollowHandle, FTimerDelegate::CreateWeakLambda(
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
		}), 0.17f, true);
}

#pragma endregion

#pragma region Blood

void AAnomaly_Object_Painting::BloodDropping()
{
	FTimerHandle BloodHandle;
	GetWorld()->GetTimerManager().SetTimer(BloodHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Niagara_Blood_Left->SetActive(true);
			Niagara_Blood_Right->SetActive(true);
		}), 15, false);
}

#pragma endregion

#pragma region Blur

void AAnomaly_Object_Painting::BlurPaint()
{
	Widget_PaintingBlur->SetVisibility(true);
	UUserWidget* UW = Widget_PaintingBlur->GetUserWidgetObject();
	UUI_PopUp_PaintingBlur* BlurWidget = Cast<UUI_PopUp_PaintingBlur>(UW);
	BlurWidget->StartPaintingBlur();
}

#pragma endregion

void AAnomaly_Object_Painting::Interacted_Implementation()
{
	bSolved = !bSolved;
}

void AAnomaly_Object_Painting::ShowInteractWidget_Implementation(bool bIsShow)
{
	UI_Interact->ShowDescription(bIsShow);
}