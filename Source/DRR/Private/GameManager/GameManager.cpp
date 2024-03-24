// GameManager.cpp

#include "GameManager/GameManager.h"

UGameManager::UGameManager()
{
	ElapsedTimer = 0.0f;
}

void UGameManager::StartTimer(UWorld* World)
{
	if (World)
	{
		World->GetTimerManager().SetTimer(TimerHandle, this, &UGameManager::UpdateTimer, 1.f, true);
	}
}

void UGameManager::StopTimer()
{
	if (TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

void UGameManager::UpdateTimer()
{
	ElapsedTimer += 1.f;
}

float UGameManager::ReturnLevel()
{
	return ElapsedTimer;
}
