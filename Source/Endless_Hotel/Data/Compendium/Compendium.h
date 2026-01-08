// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <Compendium.generated.h>

USTRUCT(BlueprintType)
struct FCompendium : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Index;

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	int32 Page;

	UPROPERTY(EditAnywhere)
	int32 Number;

	UPROPERTY(EditAnywhere)
	FString Discription;

	UPROPERTY(EditAnywhere)
	FString Path;
};