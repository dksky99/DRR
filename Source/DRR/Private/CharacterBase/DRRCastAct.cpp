// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRCastAct.h"
#include "Interface/DRRActableInterface.h"

DRRCastAct::DRRCastAct(IDRRActableInterface* Target) :DRRAct(Target)
{
}

DRRCastAct::~DRRCastAct()
{
	
}


bool DRRCastAct::BeginAct()
{
	return true;
}

bool DRRCastAct::NextReset()
{
	return true;
}

FName DRRCastAct::GetMontgeSectionName()
{
	FString CombineString = CurAct->MontageSectionPrefix + FString::FromInt(curActCount);

	return FName(*CombineString);
}

void DRRCastAct::EndAct()
{
}

bool DRRCastAct::AfterAct()
{
	return false;
}
