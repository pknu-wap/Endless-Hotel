// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Demo/UI_PopUp_Demo.h"
#include "UI/Controller/UI_Controller.h"
#include <Components/AudioComponent.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UUI_PopUp_Demo::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Faker->OnClicked.AddDynamic(this, &ThisClass::Click_QRCode);
	Button_Karina->OnClicked.AddDynamic(this, &ThisClass::Click_QRCode);
}

#pragma endregion

#pragma region Show

void UUI_PopUp_Demo::ShowWidget()
{
	Super::ShowWidget();

	auto* AC_ISeeDaeRu = UGameplayStatics::CreateSound2D(GetWorld(), SW_ISeeDaeRu);
	AC_ISeeDaeRu->Play();
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Demo::Click_QRCode()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(EWidgetType::PopUp_Demo_QR);
}

#pragma endregion