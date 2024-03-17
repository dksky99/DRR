// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/Item/DA_UseableData.h"
#include "DA_WeaponData.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDA_WeaponData : public UDA_UseableData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = weapon)
	// TSoftObjectPtr로딩을 미루고 나중에 필요할때 로딩
	TSoftObjectPtr<class USkeletalMesh> WeaponMesh;


};
