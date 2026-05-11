// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Character/EHPlayer.h"
#include "UI/Controller/UI_Controller.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/BoxComponent.h>

#pragma region Base

AAnomaly_Object_CrawlChild::AAnomaly_Object_CrawlChild(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion

#pragma region CrawlChild

void AAnomaly_Object_CrawlChild::ActivePlayTrigger()
{
	TriggerBox->SetWorldTransform(TriggerBox_Transform);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnTriggerBox);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBox);
	ShowSubTitle();
}

void AAnomaly_Object_CrawlChild::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player) return;
	AttatchChildToPlayer();
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Object_CrawlChild::AttatchChildToPlayer()
{
	bSolved = true;
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USkeletalMeshComponent* PlayerMesh = PlayerCharacter->GetMesh();
	UCharacterMovementComponent* Move = PlayerCharacter->GetCharacterMovement();
	AEHPlayerController* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
	this->AttachToComponent(PlayerMesh, AttachRules, SocketName);

	PC->bCanRun = false;
	PC->bIsRunning = false;
	PC->bCanCrouch = false;
	Move->MaxWalkSpeed = LockSpeed;
	ApplyBackwardsPenalty();
}

void AAnomaly_Object_CrawlChild::ApplyBackwardsPenalty()
{
	//Todo : 여기서 뒤로가기 키 누르면 나올 연출들
}

void AAnomaly_Object_CrawlChild::ShowSubTitle()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	FTimerHandle SubTitleTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(SubTitleTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this, UICon]()
		{
			uint8 SubtitleIndex = FMath::RandRange(0, Subtitle.Num() - 1);
			UICon->ShowSubTitle(Subtitle[SubtitleIndex], 2, 0.5f);
		}), 2, true);
}

#pragma endregion