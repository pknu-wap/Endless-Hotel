// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Components/ComboBoxKey.h>
#include <UI_ComboBox_Base.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_ComboBox_Base : public UComboBoxKey
{
	GENERATED_BODY()
	
#pragma region Font

protected:
	UPROPERTY(EditAnywhere, Category = "Setting|Font")
	FSlateFontInfo Font_ComboBox;

#pragma endregion

#pragma region Option

public:
	template <class EnumType>
	void AddEnumOption(EnumType Value)
	{
		UEnum* EnumObj = StaticEnum<EnumType>();
		AddOption(EnumObj->GetNameByIndex(static_cast<int64>(Value)));
	}

#pragma endregion

#pragma region Generate

public:
	void BindEvents();

protected:
	UFUNCTION()
	UWidget* GenerateItem(FName InKey);

#pragma endregion

#pragma region Active

public:
	UFUNCTION()
	virtual void ActiveComboBox() PURE_VIRTUAL(ThisClass::ActiveComboBox, );

	UFUNCTION()
	virtual void DeactiveComboBox(FName NameValue, ESelectInfo::Type EnumValue) PURE_VIRTUAL(ThisClass::DeactiveComboBox, );

#pragma endregion

};