// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ActData.generated.h"


UENUM()
enum class EActType : uint8
{
	ShortShot,
	Charging,
	Casting,
	Combo
};

/**
 * 
 */
UCLASS()
class DRR_API UDA_ActData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Section)
	FString ActionName;

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<class UAnimMontage> ActionMontage;
	

	UPROPERTY(EditAnywhere, Category = Section)
	FString MontageSectionPrefix;


	UPROPERTY(EditAnywhere, Category = Section)
	uint8 MaxActCount;


	UPROPERTY(EditAnywhere, Category = Section)
	TArray<float> EffectiveFrameCount;

	UPROPERTY(EditAnywhere, Category = Section)
	float FrameRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EActType Type;

};
