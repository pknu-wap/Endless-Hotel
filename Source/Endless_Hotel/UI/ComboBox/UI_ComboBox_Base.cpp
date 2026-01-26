// Copyright by 2025-2 WAP Game 2 team

#include "UI/ComboBox/UI_ComboBox_Base.h"

#pragma region Base

void UUI_ComboBox_Base::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnOpening.Clear();
	OnOpening.AddDynamic(this, &ThisClass::ActiveComboBox);

	OnSelectionChanged.Clear();
	OnSelectionChanged.AddDynamic(this, &ThisClass::DeactiveComboBox);
}

#pragma endregion

#pragma region Generate

void UUI_ComboBox_Base::BindGenerateEvent(UObject* Outer, FName FuncName)
{
	OnGenerateItemWidget.Clear();
	OnGenerateItemWidget.BindUFunction(Outer, FuncName);

	OnGenerateContentWidget.Clear();
	OnGenerateContentWidget.BindUFunction(Outer, FuncName);
}

#pragma endregion