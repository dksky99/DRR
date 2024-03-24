// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase/CharacterBase.h"
#include "Perception/AiPerceptionComponent.h"
#include "EnemyCharacterBase.generated.h"

/**
 * 
 */

//DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);
//DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangeDelegate, float /*CurrentHP*/);

UCLASS()
class AEnemyCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	AEnemyCharacterBase();
	AEnemyCharacterBase(int Type);

protected:

	uint16 EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Name")
	FString EnemyName;

	//Set Capsule Value-Kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Capsule")
	float CapsuleSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Capsule")
	float CapsuleHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Capsule")
	FString CapsuleProfileName;

	//Set Mesh Value-Kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	FVector MeshVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	FRotator MeshRotator;

	//Set Movement Value-Kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool CharacterbOrientRotationToMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	FRotator CharacterRotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterJumpZVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterAirControl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterMaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterMinAnalogWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterBrakingDecelerationWalking;

	//Set Mesh and Anim BP-Kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<class USkeletalMesh> CharacterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	TSubclassOf<class UAnimInstance> CharacterAnimBP;
	
	UAIPerceptionComponent* AIPerceptionComponent;

	class UAISensingConfig_Sight* Sight;

	uint16 Level;

	float difficulty=20;

public:
	void OnPerception(AActor* Actor, FAIStimulus stimulus);
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// UI Widget Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> EnemyHPBar;

	void SetHP(float NewHP);

	//FOnHPZeroDelegate OnHPZero;
	//FOnHPChangeDelegate OnHPChange;
};
