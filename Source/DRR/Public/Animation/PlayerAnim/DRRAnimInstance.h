// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DRRAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDRRAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float MoveThreadshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsSit : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsAttack : 1;
	
};
