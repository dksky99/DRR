// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRAct.h"
#include "Interface/DRRActableInterface.h"

DRRAct::DRRAct(IDRRActableInterface* Target)
{
	SetActs(Target);
	CurAct = Target->GetActData();
	BeginAct();
}

DRRAct::~DRRAct()
{


	for (auto f : ActFunc)
	{
		f.Unbind();
	}

}

float DRRAct::GetNextTime()
{
	return CurAct->EffectiveFrameCount[curActCount - 1]/CurAct->FrameRate;
}

uint8 DRRAct::NextAct()
{
	//범위를 1~4까지로 제한
	return curActCount = FMath::Clamp(curActCount + 1, 1, CurAct->MaxActCount);
}

bool DRRAct::NextReset()
{
	return false;
}

void DRRAct::DoAct()
{
	ActFunc[curActCount - 1].Execute();
}

const UDA_ActData* DRRAct::GetCurAct()
{
	return CurAct;
}

bool DRRAct::BeginAct()
{

	curActCount = 1;
	return false;

}

FName DRRAct::GetMontgeSectionName()
{
	return FName(TEXT("Default"));
}



void DRRAct::EndAct()
{

}


bool DRRAct::AfterAct()
{
	return true;
}

void DRRAct::SetActs(IDRRActableInterface* Target)
{
	FActionDelegate Temp;
	ActFunc = Target->GetActFunc();
	
}
