// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/Engine.h"
/**
 * 
 */
class UTILITIES_API CDisplayLog
{
public:
	CDisplayLog();
	~CDisplayLog();
public:

	template <typename FmtType, typename... Types>
	static void Log(const FmtType& Fmt, Types... Args);

	
};

template<typename FmtType, typename ...Types>
inline void CDisplayLog::Log(const FmtType& Fmt, Types ...Args)
{
	static_assert(TIsArrayOrRefOfTypeByPredicate<FmtType, TIsCharEncodingCompatibleWithTCHAR>::Value, "Formatting string must be a TCHAR array.");
	static_assert(TAnd<TIsValidVariadicFunctionArg<Types>...>::Value, "Invalid argument(s) passed to FString::Printf");
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.0f,
			FColor::Blue,
			FString::Printf(Fmt, Args...)

		);

	}
}
