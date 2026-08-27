// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include <Components/ComboBoxKey.h>
#include <CoreMinimal.h>
#include <UI_ComboBox_Base.generated.h>

UCLASS(Abstract, Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_ComboBox_Base : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region ComboBox

public:
	UComboBoxKey* GetComboBox() { return ComboBox; }

protected:
	UFUNCTION()
	virtual void OnSelectionChanged(FName NameValue, ESelectInfo::Type EnumValue) PURE_VIRTUAL(ThisClass::OnSelectionChanged, );

	template <typename EnumType>
	void GenerateItem(EnumType InKey);

private:
	UFUNCTION()
	UWidget* SetItemStyle(FName InKey);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxKey> ComboBox;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Font")
	FSlateFontInfo Font_ComboBox;

#pragma endregion

};

#pragma region ComboBox

template <typename EnumType>
FORCEINLINE void UUI_ComboBox_Base::GenerateItem(EnumType InKey)
{
	UEnum* EnumObj = StaticEnum<EnumType>();
	ComboBox->AddOption(EnumObj->GetNameByIndex(static_cast<int64>(InKey)));
}

#pragma endregion