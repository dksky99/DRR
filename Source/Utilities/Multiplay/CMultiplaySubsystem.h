// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSubsystemUtils.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CMultiplaySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccesssful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);

UCLASS()
class UTILITIES_API UCMultiplaySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UCMultiplaySubsystem();

	UFUNCTION(BlueprintCallable)
	void CreateSession(int32 NumPublicConnections, FString MatchType);

	UFUNCTION(BlueprintCallable)
	void FindSession(int32 MaxSearchResults);

	UFUNCTION(BlueprintCallable)
	void TryJoin(int32 SessionNum);

	void JoinSession(const FOnlineSessionSearchResult& SessionResult);

	UFUNCTION(BlueprintCallable)
	void LeaveSession();

	void StartSession();
	void DestroySession();
	
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	FMultiplayerOnFindSessionComplete MultiplayerOnFindSessionComplete;
	FMultiplayerOnJoinSessionComplete MultiplayerOnJoinSessionComplete;
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;

protected:
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

private:

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<class FOnlineSessionSearch>	LastSessionSearch;

	bool	bCreateSessionOnDestroy{ false };
	int32	LastNumPublicConnections;
	FString LastMatchType;

	FOnCreateSessionCompleteDelegate	CreateSessionCompleteDelegate;
	FDelegateHandle						CreateSessionCompleteDelegateHandle;
	FOnFindSessionsCompleteDelegate		FindSessionCompleteDelegate;
	FDelegateHandle						FindSessionCompleteDelegateHandle;
	FOnJoinSessionCompleteDelegate		JoinSessionCompleteDelegate;
	FDelegateHandle						JoinSessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate		StartSessionCompletetDelegate;
	FDelegateHandle						StartSessionCompleteDelegateHandle;
	FOnDestroySessionCompleteDelegate	DestroySessionCompleteDelegate;
	FDelegateHandle						DestroySessionCompleteDelegateHandle;

};
