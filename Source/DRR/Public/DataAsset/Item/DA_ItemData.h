// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ItemData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EItemType :uint8
{
	Weapon = 0,
	Consumable,
	Etc
};

UCLASS()
class DRR_API UDA_ItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EItemType Type;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Name)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Description)
	FName Description;

	
};
