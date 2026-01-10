// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"
#include "UI/PopUp/PaintingBlur/UI_PopUp_PaintingBlur.h"
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

	Mesh_Painting = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Painting"));
	SetRootComponent(Mesh_Painting);

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
	bSolved = false;
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

#pragma region FrameTilt

void AAnomaly_Object_Painting::FrameTilt()
{
	UE_LOG(LogTemp, Warning, TEXT("[FrameTilt] Called"));

	if (!GetWorld())
	{
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(FrameTiltDelayHandle);
	GetWorld()->GetTimerManager().ClearTimer(FrameTiltInterpHandle);
	FrameInitialRotMap.Empty();

	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

	for (AActor* FrameActor : AllActors)
	{
		if (!FrameActor)
		{
			continue;
		}
		USceneComponent* TargetRoot = nullptr;
		TArray<USceneComponent*> SceneComps;
		FrameActor->GetComponents<USceneComponent>(SceneComps);

		for (USceneComponent* SC : SceneComps)
		{
			if (SC && SC->ComponentHasTag(FName("FrameRoot")))
			{
				TargetRoot = SC;
				break;
			}
		}

		if (!TargetRoot)
		{
			TargetRoot = FrameActor->GetRootComponent();
		}

		if (!TargetRoot)
		{
			continue;
		}

		TargetRoot->SetMobility(EComponentMobility::Movable);

		FrameInitialRotMap.Add(FrameActor, FrameActor->GetActorRotation());
	}
	UE_LOG(LogTemp, Warning, TEXT("[FrameTilt] Targets: %d"), FrameInitialRotMap.Num());
	GetWorld()->GetTimerManager().SetTimer(FrameTiltDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			if (!GetWorld())
			{
				return;
			}

			FrameTiltStartTime = GetWorld()->GetTimeSeconds();
			FrameTiltDuration = FMath::FRandRange(FrameTiltInterpMin, FrameTiltInterpMax);
			FrameTiltTargetRoll = FMath::FRandRange(FrameTiltRollMin, FrameTiltRollMax);

			GetWorld()->GetTimerManager().SetTimer(FrameTiltInterpHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
				{
					if (!GetWorld())
					{
						return;
					}

					const float Now = GetWorld()->GetTimeSeconds();
					const float Alpha = FMath::Clamp((Now - FrameTiltStartTime) / FMath::Max(FrameTiltDuration, 0.001f), 0.f, 1.f);
					for (auto& Pair : FrameInitialRotMap)
					{
						AActor* TargetActor = Pair.Key.Get();
						if (!TargetActor)
						{
							continue;
						}

						const FRotator InitialRot = Pair.Value;
						const float NewRoll = FMath::Lerp(InitialRot.Roll, InitialRot.Roll + FrameTiltTargetRoll, Alpha);
						FRotator NewRot = InitialRot;
						NewRot.Roll = NewRoll;
						TargetActor->SetActorRotation(NewRot);
					}
					if (Alpha >= 1.f)
					{
						GetWorld()->GetTimerManager().ClearTimer(FrameTiltInterpHandle);
					}
				}), 0.02f, true);
		}), FrameTiltDelay, false);
}
#pragma endregion

#pragma region Interact

void AAnomaly_Object_Painting::SetInteraction()
{
	switch (AnomalyID)
	{
	case 0:
		break;

	default:
		InteractAction = ([this]()
			{
				AAnomaly_Object_Painting::InteractRotate();
			});
		break;
	}
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
