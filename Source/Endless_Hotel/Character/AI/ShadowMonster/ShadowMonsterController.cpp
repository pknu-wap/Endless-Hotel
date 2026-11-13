// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/ShadowMonster/ShadowMonsterController.h"
#include "ShadowMonster.h"
#include "Anomaly/Object/Neapolitan/Painting/Anomaly_Object_Painting.h"
#include "Player/Character/EHPlayer.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

void AShadowMonsterController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UnbindAppearEvents();

    Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Appear

void AShadowMonsterController::StartBind(AAnomaly_Object_Painting* OwnerPainting)
{
    UnbindAppearEvents();

    bPaintingWatched = false;
    bFaceCovered = false;

    if (!IsValid(OwnerPainting))
    {
        UpdateAppearPlayback();
        return;
    }

    BoundPainting = OwnerPainting;
    OwnerPainting->OnMonsterAppear.AddUObject(this, &ThisClass::HandleMonsterAppear);

    auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));

    if (IsValid(Player))
    {
        BoundPlayer = Player;
        Player->OnFaceCover.AddUObject(this, &ThisClass::HandleFaceCover);
    }

    UpdateAppearPlayback();
}

void AShadowMonsterController::SyncPaintingWatched(const bool bWatched)
{
    bPaintingWatched = bWatched;
    UpdateAppearPlayback();
}

void AShadowMonsterController::HandleMonsterAppear(const bool bAppear)
{
    bPaintingWatched = bAppear;
    UpdateAppearPlayback();
}

void AShadowMonsterController::HandleFaceCover(const bool bCovered)
{
    bFaceCovered = bCovered;
    UpdateAppearPlayback();
}

void AShadowMonsterController::UpdateAppearPlayback()
{
    AShadowMonster* Monster = Cast<AShadowMonster>(GetPawn());

    if (!IsValid(Monster))
    {
        return;
    }

    const bool bShouldPlay = bPaintingWatched && !bFaceCovered;

    Monster->SetAppearPlaying(bShouldPlay);

    if (!bShouldPlay)
    {
        StopMovement();
    }
}

void AShadowMonsterController::UnbindAppearEvents()
{
    if (AAnomaly_Object_Painting* Painting = BoundPainting.Get())
    {
        Painting->OnMonsterAppear.RemoveAll(this);
    }

    if (AEHPlayer* Player = BoundPlayer.Get())
    {
        Player->OnFaceCover.RemoveAll(this);
    }

    BoundPainting.Reset();
    BoundPlayer.Reset();
}

#pragma endregion