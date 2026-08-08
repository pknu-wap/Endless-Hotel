// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/MazeMonster/MazeMonster.h"
#include <Components/AudioComponent.h>

AMazeMonster::AMazeMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttackAC = CreateDefaultSubobject<UAudioComponent>(TEXT("Attack_AC"));
	AttackAC->SetupAttachment(RootComponent);

	Heartbeat_AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Heartbeat_AC"));
	Heartbeat_AC->SetupAttachment(RootComponent);
	Heartbeat_AC->bAllowSpatialization = false;
	Heartbeat_AC->bAutoActivate = false;

	CurrentIndex = 0;
}

#pragma region Attack

void AMazeMonster::PlayAttackSound()
{
	AttackAC->Play();
}

void AMazeMonster::StopAttackSound()
{
	AttackAC->Stop();
}

void AMazeMonster::AttachAttackSoundTo(
    USceneComponent* Parent,
    FName SocketName)
{
    AttackAC->AttachToComponent(
        Parent,
        FAttachmentTransformRules::SnapToTargetNotIncludingScale,
        SocketName
    );
}

void AMazeMonster::RestoreAttackSoundAttachment()
{
    AttackAC->DetachFromComponent(
        FDetachmentTransformRules::KeepWorldTransform
    );

    AttackAC->AttachToComponent(
        RootComponent,
        FAttachmentTransformRules::KeepRelativeTransform
    );
}

#pragma endregion

#pragma region Sound

void AMazeMonster::PlayHeartbeatSound()
{
	Heartbeat_AC->Play();
}

void AMazeMonster::StopHeartbeatSound()
{
	Heartbeat_AC->Stop();
}

#pragma endregion