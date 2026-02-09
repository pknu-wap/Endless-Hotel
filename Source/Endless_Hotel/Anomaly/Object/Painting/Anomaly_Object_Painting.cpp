// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"
#include "UI/Miscellaneous/PaintingBlur/UI_PaintingBlur.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SceneComponent.h>

#pragma region Base

AAnomaly_Object_Painting::AAnomaly_Object_Painting(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_LeftEye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_LeftEye"));
	Mesh_LeftEye->SetupAttachment(RootComponent);

	Mesh_RightEye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_RightEye"));
	Mesh_RightEye->SetupAttachment(RootComponent);

	Niagara_Blood_Left = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Blood_Left"));
	Niagara_Blood_Left->SetupAttachment(RootComponent);
	Niagara_Blood_Left->SetAutoActivate(false);

	Niagara_Blood_Right = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Blood_Right"));
	Niagara_Blood_Right->SetupAttachment(RootComponent);
	Niagara_Blood_Right->SetAutoActivate(false);

	Widget_PaintingBlur = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget_PaintingBlur"));
	Widget_PaintingBlur->SetupAttachment(RootComponent);
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
	Niagara_Blood_Left->SetActive(true);
	Niagara_Blood_Right->SetActive(true);
}

#pragma endregion

#pragma region Blur

void AAnomaly_Object_Painting::BlurPaint()
{
	Widget_PaintingBlur->SetVisibility(true);
	UUserWidget* UW = Widget_PaintingBlur->GetUserWidgetObject();
	UUI_PaintingBlur* BlurWidget = Cast<UUI_PaintingBlur>(UW);
	BlurWidget->StartPaintingBlur();
}

#pragma endregion

#pragma region FrameTilt

void AAnomaly_Object_Painting::FrameTilt()
{
	CurrentTilt = Root->GetRelativeRotation().Pitch;
	TargetTilt = FMath::FRandRange(10.f, 180.f);
	if (FMath::RandBool())
	{
		TargetTilt *= -1.f;
	}
	GetWorld()->GetTimerManager().SetTimer(FrameTiltHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		CurrentTilt = FMath::FInterpConstantTo(CurrentTilt, TargetTilt, GetWorld()->GetDeltaSeconds(), 1.f);
			
		const FRotator NewRot(0.f, 0.f, CurrentTilt);
		Root->SetRelativeRotation(NewRot);
		if (FMath::IsNearlyEqual(CurrentTilt, TargetTilt, 0.1f))
		{
			GetWorld()->GetTimerManager().ClearTimer(FrameTiltHandle);
		}
	}), 0.02f, true);
}
#pragma endregion

#pragma region Interact

void AAnomaly_Object_Painting::SetInteraction()
{
	Component_Interact->AdditionalAction = ([this]()
		{
			InteractRotate();
		});
}

void AAnomaly_Object_Painting::InteractRotate()
{
	OriginRotation = GetActorRotation();
	bIsRotated = !bIsRotated;
	InteractedMoveStep(0);
	bSolved = !bSolved;
}

void AAnomaly_Object_Painting::InteractedMoveStep(int32 step)
{
	// 0단계: 앞으로 나오기
	// 1단계: 뒤집기
	// 2단계: 다시 뒤로 돌아가기
	if (step > 2) return;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("InteractedMoveStep");
	LatentInfo.Linkage = step + 1;
	LatentInfo.UUID = 2000 + step;

	FVector Location;
	if (step == 2)
	{
		Location = (bIsRotated) ? InteractedLocation : DefaultLocation;
	}
	else
	{
		Location = InteractingLocation;
	}
	FRotator Rotation = (step == 0) ? OriginRotation : OriginRotation + FRotator(0, RotateAngle, 0);
	UKismetSystemLibrary::MoveComponentTo(RootComponent, Location, Rotation,
		true, true, 0.2f, false, EMoveComponentAction::Type::Move, LatentInfo);
}

#pragma endregion