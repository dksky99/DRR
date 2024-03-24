// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Weapon/DRRWeaponBase.h"
#include "DataAsset/Item/DA_WeaponData.h"

// Sets default values
ADRRWeaponBase::ADRRWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TArray<FOnActFuncDelegate> ADRRWeaponBase::GetActFunc()
{
	return TArray<FOnActFuncDelegate>();
}

FOnActFuncDelegate ADRRWeaponBase::GetBeginActFunc()
{
	FOnActFuncDelegate Temp;

	Temp.BindUObject(this, &ADRRWeaponBase::BeginFunc);

	return Temp;

}

UDA_ActData* ADRRWeaponBase::GetActData()
{
	return WeaponData->ActData;
}

// Called when the game starts or when spawned
void ADRRWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADRRWeaponBase::BeginFunc()
{
}


