// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAI.h"
#include <CoreMinimal.h>
#include <MazeMonster.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AMazeMonster : public ABaseAI
{
	GENERATED_BODY()

#pragma region Base

public:
	AMazeMonster(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Patrol

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TArray<FTransform> PatrolPoints;

	UPROPERTY(EditAnywhere, Category = "Patrol")
	uint8 CurrentIndex;

#pragma endregion

#pragma region Attack

public:
	bool bIsAttacked = false;

protected:
	UPROPERTY(EditAnywhere, Category = "Sound|Attack")
	TObjectPtr<class UAudioComponent> AttackAC;

public:
	void PlayAttackSound();
	void StopAttackSound();
	void AttachAttackSoundTo(USceneComponent* Parent, FName SocketName);
	void RestoreAttackSoundAttachment();

#pragma endregion

#pragma region Sound

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> Heartbeat_AC;

public:
	void PlayHeartbeatSound();
	void StopHeartbeatSound();

#pragma endregion

};