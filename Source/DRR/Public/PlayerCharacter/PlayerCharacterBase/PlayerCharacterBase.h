// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase/CharacterBase.h"
#include "PlayerCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API APlayerCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
	
	APlayerCharacterBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetWeapon(TSubclassOf<class ADRRWeaponBase> NewWeapon);
protected:


	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Weapon, Meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class ADRRWeaponBase> Weapon;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Weapon, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class ADRRWeaponBase> WeaponObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;

};
