// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRRAct.h"


/**
 * 
 */
class DRR_API DRRChargeAct : public DRRAct
{
public:

	DRRChargeAct(IDRRActableInterface* Target);
	~DRRChargeAct();
	virtual void ActRelease() override;
	virtual bool BeginAct() override;
	virtual bool NextReset() override;
	virtual FName GetMontgeSectionName() override;
protected:
	virtual void EndAct() override;
	virtual bool AfterAct() override;
	
protected:

};
