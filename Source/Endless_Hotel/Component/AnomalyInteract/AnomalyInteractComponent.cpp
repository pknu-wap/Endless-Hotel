#include "Component/AnomalyInteract/AnomalyInteractComponent.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"

#define LOCTEXT_NAMESPACE "Anomaly_Interaction"

void UAnomalyInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	OwnerObject = Cast<AAnomaly_Object_Base>(Owner);
}

void UAnomalyInteractComponent::SetAnomalyInteract()
{
}

#undef LOCTEXT_NAMESPACE