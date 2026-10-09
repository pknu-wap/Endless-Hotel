// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <ElevatorPassengerComponent.generated.h>

#pragma region Declare

struct FElevatorPassengerSnapshot;
class USceneComponent;
class UPrimitiveComponent;

#pragma endregion

UCLASS(ClassGroup = (Elevator), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UElevatorPassengerComponent : public UEHComponent
{
	GENERATED_BODY()

#pragma region Base

public:
	void Init(USceneComponent* InAnchor, UPrimitiveComponent* InExterior, UPrimitiveComponent* InCar);
	
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region Passenger

public:
	FElevatorPassengerSnapshot Capture() const;
	void Store() const;
	void Restore(const FElevatorPassengerSnapshot& Snap);
	void CancelRestore();

protected:
	UPROPERTY(EditAnywhere, Category = "Passenger")
	bool bDisableCollisionOnRestore = true;

	UPROPERTY(EditAnywhere, Category = "Passenger", meta = (ClampMin = "0.0"))
	float CollisionRestoreDelay = 0.05f;

private:
	void SetElevatorCollision(bool bEnable);

	UPROPERTY()
	TObjectPtr<USceneComponent> Anchor;

	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> Exterior;

	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> Car;

	FTimerHandle CollisionRestoreHandle;

#pragma endregion
	
};