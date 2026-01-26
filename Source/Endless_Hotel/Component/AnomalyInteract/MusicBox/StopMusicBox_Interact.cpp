#include "Component/AnomalyInteract/MusicBox/StopMusicBox_Interact.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "UI/World/Interact/UI_Interact.h"

#define LOCTEXT_NAMESPACE "MusicBox_Interaction"

void UStopMusicBox_Interact::SetAnomalyInteract()
{
	Super::SetAnomalyInteract();
	UUI_Interact* AnomalyUI_Interaction = OwnerObject->UI_Interact;
	AnomalyUI_Interaction->SetDescription(LOCTEXT("Key1", "오르골 끄기"));
}

#undef LOCTEXT_NAMESPACE