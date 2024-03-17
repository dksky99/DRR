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
	const class UDA_ActData* GetCurAct();
	virtual bool AfterAct();
	~DRRAct();
	float GetNextTime();
	virtual uint8 NextAct();
	virtual bool NextReset();
	void DoAct();
	virtual bool BeginAct();
	virtual FName GetMontgeSectionName();
protected:
	virtual void EndAct();
	
private:
	void SetActs(class IDRRActableInterface* Target);

protected:

	TArray<FOnActFuncDelegate> ActFunc;
	uint8 curActCount;
	TObjectPtr<class UDA_ActData> CurAct;
	

};


