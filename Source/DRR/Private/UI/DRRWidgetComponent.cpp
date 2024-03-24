// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DRRWidgetComponent.h"
#include "UI/DRRUserWidget.h"

void UDRRWidgetComponent::InitWidget()
{
	Super::InitWidget();
	
	UDRRUserWidget* DRRUserWidget = Cast<UDRRUserWidget>(GetWidget());
	if (DRRUserWidget)
	{
		DRRUserWidget->SetOwningActor(GetOwner());
	}
}
