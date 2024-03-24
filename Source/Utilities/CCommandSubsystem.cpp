// Fill out your copyright notice in the Description page of Project Settings.


#include "CCommandSubsystem.h"
#include "Multiplay/CMultiplaySubsystem.h"
#include "Utilities/UtilityList.h"

UCCommandSubsystem::UCCommandSubsystem()
{

}

void UCCommandSubsystem::Host()
{
	GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>()->CreateSession(4,"FreeForAll");
	
}

void UCCommandSubsystem::Join_Address()
{

}

void UCCommandSubsystem::Find()
{
	GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>()->MultiplayerOnFindSessionComplete.AddUObject(this, &UCCommandSubsystem::FindFinish);
	GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>()->FindSession(10000);
	
}

void UCCommandSubsystem::Join(uint32 RoomNum)
{
	GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>()->TryJoin(RoomNum);
	
}

void UCCommandSubsystem::FindFinish(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful)
{
	for (int i=0;i<SessionResults.Num();i++)
	{
		CDisplayLog::Log(TEXT("%d ¹ø ¹æ : "),i);
	}

	GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>()->MultiplayerOnFindSessionComplete.Clear();

}
