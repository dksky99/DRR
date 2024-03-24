// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UGameManager : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UGameManager();

	void StartTimer(UWorld* World);
	void StopTimer();
	void UpdateTimer();

	float ReturnLevel();
	
private:
	FTimerHandle TimerHandle;
	float ElapsedTimer;

};
