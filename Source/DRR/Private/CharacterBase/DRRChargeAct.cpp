// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRChargeAct.h"
#include "Interface/DRRActableInterface.h"

DRRChargeAct::DRRChargeAct(IDRRActableInterface* Target) :DRRAct(Target)
{
}

DRRChargeAct::~DRRChargeAct()
{
}

void DRRChargeAct::ActRelease()
{
	AfterAct();
}

bool DRRChargeAct::BeginAct()
{
	return true;
}

bool DRRChargeAct::NextReset()
{
	return true;
}

FName DRRChargeAct::GetMontgeSectionName()
{
	FString CombineString = CurAct->MontageSectionPrefix + FString::FromInt(curActCount);

	return FName(*CombineString);
}


void DRRChargeAct::EndAct()
{
}

bool DRRChargeAct::AfterAct()
{
	return false;
}
