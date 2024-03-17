// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <string>
DECLARE_LOG_CATEGORY_EXTERN(GoomDolRah, Display, All);
/**
 * 
 */
class UTILITIES_API CLog
{
public:
	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(bool InValue);
	static void Log(FVector InValue);
	static void Log(FString InValue);
	static void Log(const FString& InFuncName, int32 InLineNumber);
	static void Log(const UObject* InObject);
	static void Log(const char* InValue);

	//모든 UEnum타입을 대상으로 시도하는중
	//template<typename T>
	//static void Log(T EnumValue);

};
/*
template<typename T>
inline void CLog::Log(T EnumValue)
{

	static_assert(TIsEnumClass<T>::Value, "It Must Enum Type");
	UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *T::StaticClass()->GetEnumName(), true);
	if (!EnumPtr)
	{
		UE_LOG(GoomDolRah, Error, TEXT("Failed to find enum!"));
		return;
	}

	// Enum 값의 문자열 표현을 가져옵니다.
	FName EnumString = EnumPtr->GetEnumByValue(<int64>(EnumValue));
	if (EnumString.IsEmpty())
	{
		UE_LOG(GoomDolRah, Error, TEXT("Failed to get enum string!"));
		return;
	}

	// 로그로 Enum 값의 문자열 표현을 출력합니다.
	UE_LOG(GoomDolRah, Display, TEXT("Enum value: %s"), *EnumString);

}
*/