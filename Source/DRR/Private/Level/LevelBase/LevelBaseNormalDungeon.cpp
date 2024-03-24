// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelBase/LevelBaseNormalDungeon.h"
#include "GameManager/GameManager.h"

ALevelBaseNormalDungeon::ALevelBaseNormalDungeon()
{
    
}

void ALevelBaseNormalDungeon::BeginPlay()
{
    Super::BeginPlay();

    // GetGameManager
    UGameManager* GameInstance = Cast<UGameManager>(GetGameInstance());
    if (GameInstance)
    {
        //LevelTimerStart
        GameInstance->StartTimer(GetWorld());
    }
}

void ALevelBaseNormalDungeon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    UGameManager* GameInstance = Cast<UGameManager>(GetGameInstance());
    if (GameInstance)
    {
        //LevelTimerStop
        GameInstance->StopTimer();
    }
}