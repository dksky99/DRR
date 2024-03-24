// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Weapon/DRRWeapon1.h"
#include "Utilities/UtilityList.h"

TArray<FOnActFuncDelegate> ADRRWeapon1::GetActFunc()
{
	TArray<FOnActFuncDelegate> FuncArray;
	FOnActFuncDelegate Temp;
	Temp.BindUObject(this, &ADRRWeapon1::Func1);
	FuncArray.Add(Temp);
	Temp.BindUObject(this, &ADRRWeapon1::Func2);
	FuncArray.Add(Temp);
	Temp.BindUObject(this, &ADRRWeapon1::Func3);
	FuncArray.Add(Temp);

	return FuncArray;
}

FOnActFuncDelegate ADRRWeapon1::GetBeginActFunc()
{
	FOnActFuncDelegate Temp;

	return Temp;
 
}

void ADRRWeapon1::BeginFunc()
{
	CLog::Log("BeginFunc");

}

void ADRRWeapon1::Func1()
{
	CLog::Log("Func1");
}

void ADRRWeapon1::Func2()
{
	CLog::Log("Func2");
}

void ADRRWeapon1::Func3()
{
	CLog::Log("Func3");
}
