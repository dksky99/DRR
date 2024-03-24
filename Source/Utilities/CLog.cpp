#include "Utilities/CLog.h"

#include <string>
DEFINE_LOG_CATEGORY(GoomDolRah);



void CLog::Log(int32 InValue)
{

	UE_LOG(GoomDolRah, Display, TEXT("%d"), InValue);
}

void CLog::Log(float InValue)
{

	UE_LOG(GoomDolRah, Display, TEXT("%f"), InValue);
}

void CLog::Log(bool InValue)
{
	if (InValue)
	{

		UE_LOG(GoomDolRah, Display, TEXT("True"));


	}
	else
	{
		UE_LOG(GoomDolRah, Display, TEXT("False"));

	}

}

void CLog::Log(FVector InValue)
{

	FString str = InValue.ToString();

	UE_LOG(GoomDolRah, Display, TEXT("%s"), *str);
}

void CLog::Log(FString InValue)
{

	UE_LOG(GoomDolRah, Display, TEXT("%s"), *InValue);
}

void CLog::Log(const FString& InFuncName, int32 InLineNumber)
{


	FString str;
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));

	UE_LOG(GoomDolRah, Display, TEXT("%s"), *str);
}

void CLog::Log(const UObject* InObject)
{

	FString str;

	if (!!InObject)
	{
		str.Append(*InObject->GetName());

	}
	std::string s;
	s.append("hello");
	
	str.Append(!InObject ? "Not Valid" : "Valid");
	UE_LOG(GoomDolRah, Display, TEXT("%s"), *str);

}
void CLog::Log(const char* InValue)
{
	FString str(InValue);
	UE_LOG(GoomDolRah, Display, TEXT("%s"), *str);

}

