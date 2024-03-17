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
public:

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetWeapon(TSubclassOf<class ADRRWeaponBase> NewWeapon);

	virtual void WeaponAttackPress();
	virtual void WeaponAttackRelaease();
	
protected:


	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Weapon, Meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class ADRRWeaponBase> Weapon;

	//UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Weapon, Meta = (AllowPrivateAccess = "true"));
	//TObjectPtr<class ADRRWeaponBase> WeaponObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;


	//인풋매핑콘택스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> defaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ActPressAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ActReleaseAction;

};
