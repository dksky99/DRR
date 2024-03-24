// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRRUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }
	FORCEINLINE void SetMaxHP(float NewHP) { MaxHP = NewHP; }
	void UpdateHP(float NewHP);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actor)
	TObjectPtr<AActor> OwningActor;

	TObjectPtr<class UProgressBar> HPProgressBar;
	float MaxHP;
};
