// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8 
{
	Shoulder,
	Quater
};

UCLASS()
class DRR_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:

	virtual void SetCharacterControlData(const class UCharacterControlDataAsset* CharacterControlData);

protected:
	TMap< ECharacterControlType, class UCharacterControlDataAsset*> CharacterControlManager; // 생성자가 호출될떄 같이 메모리 할당


	


};
