// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRComboAct.h"
#include "Interface/DRRActableInterface.h"

DRRComboAct::DRRComboAct(IDRRActableInterface* Target) :DRRAct(Target)
{

}

DRRComboAct::~DRRComboAct()
{
}

bool DRRComboAct::BeginAct()
{
	return false;
}

bool DRRComboAct::NextReset()
{
	return false;
}

FName DRRComboAct::GetMontgeSectionName()
{

	FString CombineString = CurAct->MontageSectionPrefix + FString::FromInt(curActCount);

	return FName(*CombineString);
}

void DRRComboAct::EndAct()
{
}

bool DRRComboAct::AfterAct()
{
	return true;
}
