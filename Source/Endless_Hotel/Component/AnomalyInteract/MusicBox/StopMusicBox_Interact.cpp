#include "Component/AnomalyInteract/MusicBox/StopMusicBox_Interact.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Anomaly/Object/MusicBox/Anomaly_Object_MusicBox.h"
#include <Components/AudioComponent.h>

#define LOCTEXT_NAMESPACE "MusicBox_Interaction"

void UStopMusicBox_Interact::SetAnomalyInteract()
{
	AnomalyDescription = LOCTEXT("Key1", "오르골 끄기");
	Super::SetAnomalyInteract();
}

void UStopMusicBox_Interact::Interacted_Implementation()
{
	Cast<AAnomaly_Object_MusicBox>(OwnerObject)->StopMusicBox();
}

#undef LOCTEXT_NAMESPACE