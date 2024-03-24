// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/Animation/DRRActAnimNotify.h"
#include "Interface/DRRActorInterface.h"

void UDRRActAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	IDRRActorInterface* ActorInterface=Cast<IDRRActorInterface>(MeshComp->GetOwner());
	if (ActorInterface)
	{
		ActorInterface->Act();
	}

}
