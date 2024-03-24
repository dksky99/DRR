// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelBaseNormalDungeon.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ALevelBaseNormalDungeon : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	ALevelBaseNormalDungeon();

	virtual void BeginPlay()override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

};
