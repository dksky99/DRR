// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


DECLARE_DELEGATE(FActionDelegate);
/**
 * 
 */
class DRR_API DRRAct
{
public:

	DRRAct(class IDRRActableInterface* Target);
	virtual void ActRelease();
	const class UDA_ActData* GetCurAct();
	virtual bool AfterAct();
	~DRRAct();
	virtual float GetNextTime();
	virtual uint8 NextAct();
	virtual bool NextReset();
	void DoBeginAct();
	void DoAct();
	virtual bool BeginAct();
	virtual FName GetMontgeSectionName();
protected:
	virtual void EndAct();
	
private:
	void SetActs(class IDRRActableInterface* Target);

protected:

	FOnActFuncDelegate BeginActFunc;
	TArray<FOnActFuncDelegate> ActFunc;
	uint8 curActCount;
	uint8 curFuncCount;
	TObjectPtr<class UDA_ActData> CurAct;
	

};


