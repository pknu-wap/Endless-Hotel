// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Components/ComboBoxKey.h>
#include <UI_ComboBox_Base.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_ComboBox_Base : public UComboBoxKey
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void SynchronizeProperties() override;

#pragma endregion

#pragma region Font

public:
	const FSlateFontInfo& GetFont() const { return Font_ComboBox; }

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
	void BindGenerateEvent(UObject* Outer, FName FuncName);

#pragma endregion

#pragma region Active

protected:
	UFUNCTION()
	virtual void ActiveComboBox() PURE_VIRTUAL(ThisClass::ActiveComboBox, );

	UFUNCTION()
	virtual void DeactiveComboBox(FName NameValue, ESelectInfo::Type EnumValue) PURE_VIRTUAL(ThisClass::DeactiveComboBox, );

#pragma endregion

};