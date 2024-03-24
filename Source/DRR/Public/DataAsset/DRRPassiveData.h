// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DRRPassiveData.generated.h"



UENUM()
enum class EPassiveType : uint8
{
	Always=0,
	WhenHitting,
	WhenHit,
	WhenDodging
};
UENUM()
enum class EPassiveStateType : uint8
{

	buff,
	debuff
};


UCLASS()
class DRR_API UDRRPassiveData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = Section)
	FString PassiveName;

	UPROPERTY(EditAnywhere, Category = Section)
	float PassiveDelay;

	UPROPERTY(EditAnywhere, Category = Section)
	float PassiveCoolDown;


	UPROPERTY(EditAnywhere, Category = Section)
	float PassiveDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EPassiveType Type;

};
