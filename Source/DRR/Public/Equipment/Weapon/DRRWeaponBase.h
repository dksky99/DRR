// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/DRRActableInterface.h"
#include "DRRWeaponBase.generated.h"

UCLASS()
class DRR_API ADRRWeaponBase : public AActor,public IDRRActableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADRRWeaponBase();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;
	virtual FOnActFuncDelegate GetBeginActFunc() override;
	virtual class UDA_ActData* GetActData() override;

	class UDA_WeaponData* GetWeaponData() { return WeaponData; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginFunc() ;

public:	


protected:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AttackData)
	TObjectPtr<class UDA_WeaponData> WeaponData;





};
