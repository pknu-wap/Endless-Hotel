// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIController.h"
#include <CoreMinimal.h>
#include <ShadowMonsterController.generated.h>

#pragma region Declare

class AAnomaly_Object_Painting;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AShadowMonsterController : public ABaseAIController
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region Appear

public:
	void StartBind(AAnomaly_Object_Painting* OwnerPainting);
	void SyncPaintingWatched(bool bWatched);

private:
	void HandleMonsterAppear(bool bAppear);
	void HandleFaceCover(bool bCovered);
	void UpdateAppearPlayback();
	void UnbindAppearEvents();

private:
	TWeakObjectPtr<AAnomaly_Object_Painting> BoundPainting;
	TWeakObjectPtr<class AEHPlayer> BoundPlayer;

	bool bPaintingWatched = false;
	bool bFaceCovered = false;

#pragma endregion
	
};