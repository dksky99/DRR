// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRAct.h"
#include "Interface/DRRActableInterface.h"
#include "Utilities/UtilityList.h"

DRRAct::DRRAct(IDRRActableInterface* Target)
{
	CLog::Log("DDRAct");
	SetActs(Target);
	CLog::Log(Target == nullptr);
	CurAct = Target->GetActData();
	BeginAct();
}

void DRRAct::ActRelease()
{

}

DRRAct::~DRRAct()
{
	BeginActFunc.Unbind();

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

	CLog::Log("DRRAct::NextAct");
	CLog::Log(curActCount);
	return curActCount = FMath::Clamp(curActCount + 1, 1, CurAct->MaxActCount);
}

bool DRRAct::NextReset()
{
	return false;
}

void DRRAct::DoBeginAct()
{
	CLog::Log("DRRAct::DoAct");
	if (BeginActFunc.IsBound())
	{
		BeginActFunc.Execute();

	}
	
}

void DRRAct::DoAct()
{
	CLog::Log("DRRAct::DoAct");
	ActFunc[curFuncCount%ActFunc.Num()].Execute();
}

const UDA_ActData* DRRAct::GetCurAct()
{
	return CurAct;
}

bool DRRAct::BeginAct()
{

	CLog::Log("DRRAct::BeginAct");
	curActCount = 1;
	curFuncCount = 0;
	return false;

}

FName DRRAct::GetMontgeSectionName()
{
	CLog::Log("DRRAct::GetMontgeSectionName");
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
	CLog::Log("DRRAct::SetActs");
	BeginActFunc = Target->GetBeginActFunc();
	ActFunc = Target->GetActFunc();
	CLog::Log(ActFunc.Num());
	
	
}
