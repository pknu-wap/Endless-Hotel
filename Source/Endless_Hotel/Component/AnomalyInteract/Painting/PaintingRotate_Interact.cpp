#include "Component/AnomalyInteract/Painting/PaintingRotate_Interact.h"
#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"

#define LOCTEXT_NAMESPACE "PaintingRotate_Interaction"

void UPaintingRotate_Interact::SetAnomalyInteract()
{
	AnomalyDescription = LOCTEXT("Key1", "액자 뒤집기");
	Super::SetAnomalyInteract();
}

void UPaintingRotate_Interact::Interacted_Implementation()
{
	Cast<AAnomaly_Object_Painting>(OwnerObject)->InteractRotate();
}

#undef LOCTEXT_NAMESPACE