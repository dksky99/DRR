// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/DRRActorInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class DRR_API ACharacterBase : public ACharacter ,public IDRRActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	//추가 사항2
	virtual void Act() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:

	//행동 컴포넌트. 추가사항1
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Act, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UDRRActComponent> ActComponent;


};
