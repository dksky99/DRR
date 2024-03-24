// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplay/CMultiplaySubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSessionSettings.h"


UCMultiplaySubsystem::UCMultiplaySubsystem()
	: CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
	, FindSessionCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete))
	, JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete))
	, StartSessionCompletetDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
	, DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete))
{
	// SessionInterface
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}

void UCMultiplaySubsystem::CreateSession(int32 NumPublicConnections, FString MatchType)
{
	if (!SessionInterface.IsValid())
		return;

	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		bCreateSessionOnDestroy = true;
		LastNumPublicConnections = NumPublicConnections;
		LastMatchType = MatchType;

		DestroySession();
	}

	// Add CreateSessionCompleteDelegate to the session interface delegate list.
	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	// Setting options for a new session
	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false; // NULL일 경우 LAN 연결
	LastSessionSettings->NumPublicConnections = NumPublicConnections;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bAllowInvites = true;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->bIsDedicated = false;
	LastSessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	LastSessionSettings->BuildUniqueId = 1;

	// Create Session
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		// Remove the delegate from the delegate list using the handle.
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		UE_LOG(LogNet, Error, TEXT("%s: couldn't Create session."), *GetFullName())
		// Broadcast that the session creation has failed.
		MultiplayerOnCreateSessionComplete.Broadcast(false);
	}
}

void UCMultiplaySubsystem::FindSession(int32 MaxSearchResults)
{
	if (!SessionInterface.IsValid())
		return;

	// Add FindSessionCompleteDelegate to the session interface delegate list.
	FindSessionCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);

	// Setting session search options
	LastSessionSearch = MakeShareable(new FOnlineSessionSearch);
	LastSessionSearch->MaxSearchResults = MaxSearchResults;
	UE_LOG(LogNet, Error, TEXT("%s: Session Type"), IOnlineSubsystem::Get()->GetSubsystemName())
	LastSessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	LastSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	UE_LOG(LogNet, Error, TEXT("%s: Try Find session."), *GetFullName())
	// Find sessions
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
	{

		UE_LOG(LogNet, Error, TEXT("%s: couldn't Find session."), *GetFullName())
		// Clear the delegate from the delegate list
		SessionInterface->ClearOnCancelFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegateHandle);
		// Broadcast the result 
		MultiplayerOnFindSessionComplete.Broadcast(TArray<FOnlineSessionSearchResult>(), false);

	}

}

void UCMultiplaySubsystem::TryJoin(int32 SessionNum)
{
	if (SessionInterface)
	{
		// Claer the delegate from the delegate list using the handle
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegateHandle);
	}

	if (LastSessionSearch->SearchResults.Num() <= SessionNum)
	{

		return;
	}
	
	JoinSession(LastSessionSearch->SearchResults[SessionNum]);
}

void UCMultiplaySubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
	if (!SessionInterface.IsValid())
	{

		UE_LOG(LogNet, Error, TEXT("%s: SI Not Valid."), *GetFullName())
		MultiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
		return;
	}

	// Add JoinSessionCompleteDelegate to the session interface delegate list.
	JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionResult))
	{
		// Clear the delegate from the delegate list
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
		// Broadcast the result 
		MultiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
	}

}

void UCMultiplaySubsystem::LeaveSession()
{
	if (!SessionInterface.IsValid())
		return;
	if (SessionInterface->GetNamedSession(NAME_GameSession))
	{
		





		SessionInterface->DestroySession(NAME_GameSession);
	}

}

void UCMultiplaySubsystem::StartSession()
{
}

void UCMultiplaySubsystem::DestroySession()
{
	if (!SessionInterface.IsValid())
	{
		MultiplayerOnDestroySessionComplete.Broadcast(false);
		return;
	}

	// Add DestroySessionCompleteDelegate to the session interface delegate list.
	DestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);

	if (!SessionInterface->DestroySession(NAME_GameSession))
	{
		// Clear the delegate from the delegate list
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
		// Broadcast the result 
		MultiplayerOnDestroySessionComplete.Broadcast(false);
	}
}

void UCMultiplaySubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (SessionInterface)
	{
		// Claer the delegate from the delegate list using the handle
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}

	UE_LOG(LogNet, Error, TEXT("%s: Create session Success"), *GetFullName())
	// Broadcast a success message for the session creation.
	MultiplayerOnCreateSessionComplete.Broadcast(true);
	//상속받은로컬플레이어 필요
	//Cast<>(LPC.GetLocalPlayer())->CurrentLevel = ECurrentLevel::SomeLevel;
	//이동할 레벨
	GetWorld()->ServerTravel("/Game/Level/StartDungeon?listen");
}

void UCMultiplaySubsystem::OnFindSessionComplete(bool bWasSuccessful)
{
	if (SessionInterface)
	{
		// Claer the delegate from the delegate list using the handle
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegateHandle);
	}

	if (LastSessionSearch->SearchResults.Num() <= 0)
	{

		UE_LOG(LogNet, Error, TEXT("%s: Zero Find"), *GetFullName())
		// Session results was empty => false
		MultiplayerOnFindSessionComplete.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
		return;
	}


	UE_LOG(LogNet, Error, TEXT("%s: Find Success"), *GetFullName())
	// Broadcast a success message for the session finding.
	MultiplayerOnFindSessionComplete.Broadcast(LastSessionSearch->SearchResults, bWasSuccessful);
}

void UCMultiplaySubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (SessionInterface)
	{
		// Claer the delegate from the delegate list using the handle
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
	}

	// Broadcast a message for the session joining with the result.
	MultiplayerOnJoinSessionComplete.Broadcast(Result);
	if (GetGameInstance()->ClientTravelToSession(GetWorld()->GetFirstLocalPlayerFromController()->GetControllerId(), NAME_GameSession))
	{

		UE_LOG(LogNet, Error, TEXT("%s: Travel Success"), *GetFullName())
		//Cast<UMyLocalPlayer>(LPC.GetLocalPlayer())->CurrentLevel = NewLevel;
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("%s: travel to session failed"), *GetFullName())
	}
}

void UCMultiplaySubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void UCMultiplaySubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
	}

	if (bWasSuccessful && bCreateSessionOnDestroy)
	{
		bCreateSessionOnDestroy = false;
		CreateSession(LastNumPublicConnections, LastMatchType);
	}

	MultiplayerOnDestroySessionComplete.Broadcast(bWasSuccessful);
}