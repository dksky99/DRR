// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/Item/DA_ItemData.h"
#include "DA_UseableData.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDA_UseableData : public UDA_ItemData
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActData)
	TObjectPtr<class UDA_ActData> ActData;

};
