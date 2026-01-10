// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EHPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_HOTEL_API UEHPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
    bool bIsAnomalyGenerated = false;


protected:
    // 실제 현재 속도
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float ActualSpeed = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float ActualSpeed_X = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float ActualSpeed_Y = 0.f;

    // 목표 속도
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float TargetSpeed = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float TargetSpeed_X = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float TargetSpeed_Y = 0.f;

    // 최종 애니메이션용 속도 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float HorizontalSpeed; // 좌우 성분

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float VerticalSpeed;   // 전후 성분

    // 컨트롤러에서 가져오는 상태 값
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
    bool bIsRunningState = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
    bool bIsCrouchingState = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
    bool bIsFaceCoveringState = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
    bool bIsButtonPressingState = false;
    // 캐싱
    UPROPERTY(BlueprintReadOnly, Category = "Anim")
    APawn* CachedPawnOwner;

    // 달리기 애니메이션 속도 배율
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float RunSpeedMultiplier = 2.0f;

    // 속도 보간 값
    const float InterpSpeedValue = 20.0f;
    const float StopThreshold = 5.0f;
};
