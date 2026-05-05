// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

class ENDLESS_HOTEL_API EnumConverter
{
public:
	template <class EnumClass>
	static FName GetEnumAsName(EnumClass EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();

		return static_cast<FName>(*EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString());
	}

	template <class EnumClass>
	static FString GetEnumAsString(EnumClass EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();

		return *EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString();
	}

	template <class EnumClass>
	static FText GetEnumAsText(EnumClass EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();

		return EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue));
	}
};