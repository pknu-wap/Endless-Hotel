// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

class ENDLESS_HOTEL_API EnumConverter
{
public:
	template <class EnumClass>
	static FName GetNameFromEnum(EnumClass EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();

		return static_cast<FName>(*EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString());
	}

	template <class EnumClass>
	static FString GetStringFromEnum(EnumClass EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();

		return *EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString();
	}

	template <class EnumClass>
	static FText GetTextFromEnum(EnumClass EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();

		return EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue));
	}

	template <class EnumClass>
	static EnumClass GetEnumFromName(const FName NameValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();
		int64 IntValue = EnumPtr->GetValueByNameString(NameValue);

		return static_cast<EnumClass>(IntValue);
	}

	template <class EnumClass>
	static EnumClass GetEnumFromString(const FString StringValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();
		int64 IntValue = EnumPtr->GetValueByNameString(StringValue);

		return static_cast<EnumClass>(IntValue);
	}

	template <class EnumClass>
	static EnumClass GetEnumFromText(const FText TextValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();
		int64 IntValue = EnumPtr->GetValueByNameString(TextValue);

		return static_cast<EnumClass>(IntValue);
	}
};