// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRAct.h"
#include "Interface/DRRActableInterface.h"
#include "Utilities/UtilityList.h"

DRRAct::DRRAct()
{

}

void DRRAct::SetActor(IDRRActableInterface* Target)
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
	if (BeginActFunc.IsBound())
	{
		BeginActFunc.Unbind();

	}
	if (BeginActFunc.IsBound())
	{
		EndActFunc.Unbind();

	}
	for (FOnActFuncDelegate f : ActFunc)
	{
		f.Unbind();
	}
	ActFunc.Empty();
}

float DRRAct::GetNextTime()
{
	return CurAct->EffectiveFrameCount[curActCount - 1]/CurAct->FrameRate;
}

uint8 DRRAct::NextAct()
{
	//������ 1~4������ ����

	CLog::Log("DRRAct::NextAct");
	CLog::Log(curActCount);
	return curActCount = FMath::Clamp(curActCount + 1, 1, CurAct->MaxActCount);
}

bool DRRAct::NextReset()
{
	return false;
}

FOnActFuncDelegate DRRAct::DoBeginAct()
{
	CLog::Log("DRRAct::DoAct");
	
	return BeginActFunc;
	
}

FOnActFuncDelegate DRRAct::DoAct()
{
	CLog::Log("DRRAct::DoAct");
	return (ActFunc[curFuncCount++]);
}

FOnActFuncDelegate DRRAct::DoEndAct()
{
	return EndActFunc;
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
	if (BeginActFunc.IsBound())
	{
		BeginActFunc.Unbind();

	}
	if (BeginActFunc.IsBound())
	{
		EndActFunc.Unbind();

	}
	for (FOnActFuncDelegate f : ActFunc)
	{
		f.Unbind();
	}
	ActFunc.Empty();

}


bool DRRAct::AfterAct()
{
	return true;
}

void DRRAct::SetActs(IDRRActableInterface* Target)
{
	CLog::Log("DRRAct::SetActs");
	BeginActFunc = Target->GetBeginActFunc();
	ActFunc = Target->GetActFunc( );
	EndActFunc = Target->GetEndActFunc();
	CLog::Log(ActFunc.Num());
	
	
}
